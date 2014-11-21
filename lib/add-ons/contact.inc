<?php
/**
 * Form constructor for the site-wide contact form.
 *
 * @see contact_site_form_validate()
 * @see contact_site_form_submit()
 * @ingroup forms
 */
function BootstrapBlocks_preprocess_contact_site_form($form, &$form_state) {
  global $user;

  // Check if flood control has been activated for sending e-mails.
  $limit = variable_get('contact_threshold_limit', 5);
  $window = variable_get('contact_threshold_window', 3600);
  if (!flood_is_allowed('contact', $limit, $window) && !user_access('administer contact forms')) {
    drupal_set_message(t("You cannot send more than %limit messages in @interval. Try again later.", array('%limit' => $limit, '@interval' => format_interval($window))), 'error');
    drupal_access_denied();
    drupal_exit();
  }

  // Get an array of the categories and the current default category.
  $categories = db_select('contact', 'c')
    ->addTag('translatable')
    ->fields('c', array('cid', 'category'))
    ->orderBy('weight')
    ->orderBy('category')
    ->execute()
    ->fetchAllKeyed();
  $default_category = db_query("SELECT cid FROM {contact} WHERE selected = 1")->fetchField();

  // If there are no categories, do not display the form.
  if (!$categories) {
    if (user_access('administer contact forms')) {
      drupal_set_message(t('The contact form has not been configured. <a href="@add">Add one or more categories</a> to the form.', array('@add' => url('admin/structure/contact/add'))), 'error');
    }
    else {
      drupal_not_found();
      drupal_exit();
    }
  }

  // If there is more than one category available and no default category has
  // been selected, prepend a default placeholder value.
  if (!$default_category) {
    if (count($categories) > 1) {
      $categories = array(0 => t('- Please choose -')) + $categories;
    }
    else {
      $default_category = key($categories);
    }
  }

  if (!$user->uid) {
    $form['#attached']['library'][] = array('system', 'jquery.cookie');
    $form['#attributes']['class'][] = 'user-info-from-cookie';
  }

  $form['#attributes']['class'][] = 'contact-form';
  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Your name'),
    '#maxlength' => 255,
    '#default_value' => $user->uid ? format_username($user) : '',
    '#required' => TRUE,
  );
  $form['mail'] = array(
    '#type' => 'textfield',
    '#title' => t('Your e-mail address'),
    '#maxlength' => 255,
    '#default_value' => $user->uid ? $user->mail : '',
    '#required' => TRUE,
  );
  $form['subject'] = array(
    '#type' => 'textfield',
    '#title' => t('Subject'),
    '#maxlength' => 255,
    '#required' => TRUE,
  );
  $form['cid'] = array(
    '#type' => 'select',
    '#title' => t('Category'),
    '#default_value' => $default_category,
    '#options' => $categories,
    '#required' => TRUE,
    '#access' => count($categories) > 1,
  );
  $form['message'] = array(
    '#type' => 'textarea',
    '#title' => t('Message'),
    '#required' => TRUE,
  );
  // We do not allow anonymous users to send themselves a copy
  // because it can be abused to spam people.
  $form['copy'] = array(
    '#type' => 'checkbox',
    '#title' => t('Send yourself a copy.'),
    '#access' => $user->uid,
  );
  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Send message'),
  );

  return $form . 'xxx';
}