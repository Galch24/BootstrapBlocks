<?php

/**
 * удаляем лишние классы из всех представлений
 * 
 * Preprocess the primary theme implementation for a view.
 * @see template_preprocess_views_view in views/theme/theme.inc
 * array_keys($vars) = Array(
    [0] => view
    [1] => view_array
    [2] => theme_hook_suggestions
    [3] => zebra
    [4] => id
    [5] => directory
    [6] => classes_array
    [7] => attributes_array // пустой массив
    [8] => title_attributes_array
    [9] => content_attributes_array
    [10] => title_prefix
    [11] => title_suffix
    [12] => user
    [13] => db_is_active
    [14] => is_admin
    [15] => logged_in
    [16] => is_front
    [17] => rows
    [18] => css_name  // равен catalog, price и т.д.
    [19] => name
    [20] => display_id
    [21] => css_class // пуст
    [22] => header
    [23] => footer
    [24] => exposed
    [25] => more
    [26] => feed_icon
    [27] => pager
    [28] => title
    [29] => attachment_before
    [30] => attachment_after
    [31] => dom_id
)
 */

function BootstrapBlocks_preprocess_views_view(&$vars) {
  //print '<pre>before = '. check_plain(print_r($vars['classes_array'], 1)) .'</pre>';

  $vars['classes_array'][2] = ''; // удаляем класс типа "view-id-bank"
  $vars['classes_array'][3] = str_replace('view-display-id','vd',$vars['classes_array'][3]);
  $vars['classes_array'][count($vars['classes_array'])-1] = ''; // deleting the last class, etc. "view-dom-id-6b5b7c31e4afa0fbca33eb46fc5d1d3c"
  /*
   * 
   * view view-install view-id-install view-display-id-install view-dom-id-ac40f0b1cf3285e8e11f1816be7fe2d7  
  */  
    
  // Flatten the classes to a string for the template file.
  $vars['classes'] = trim(implode(' ', $vars['classes_array'])); //удаляем пробелы из начала и конца строки
  //print '<pre>after = '. check_plain(print_r($vars['classes_array'], 1)) .'</pre>';
  return TRUE;
}

/**
 * Удаляем лишние классы из полей
 * 
 * Preprocess theme function to print a single record from a row, with fields
 * @see template_preprocess_views_view_fields in views/theme/theme.inc
 *setlocale(LC_ALL, 'ru_RU.UTF-8');
 * print $type . '<pre> $data = '. check_plain(print_r($url, 1)) .'</pre>';
 * [а-яА-Я]
 * print '<pre>$data = '. check_plain(print_r(array_keys($vars), 1)) .'</pre>';
    array_keys($vars) = Array (
    [0] => view
    [1] => options
    [2] => row
    [3] => field_alias
    [4] => theme_hook_suggestion
    [5] => theme_hook_suggestions
    [6] => zebra
    [7] => id
    [8] => directory
    [9] => classes_array
    [10] => attributes_array
    [11] => title_attributes_array
    [12] => content_attributes_array
    [13] => title_prefix
    [14] => title_suffix
    [15] => user
    [16] => db_is_active
    [17] => is_admin
    [18] => logged_in
    [19] => is_front
    [20] => fields
)
 */
function BootstrapBlocks_preprocess_views_view_fields(&$vars) {
    $fields = $vars['fields'];

    //print '<pre>$data = '. check_plain(print_r($fields['field_semin_pict']->class, 1)) .'</pre>';
    foreach ($fields as $id => $field) {
        $field->wrapper_prefix = trim(str_replace('views-field views-field-','',$field->wrapper_prefix));
    }
}

/**
 * Alternative view of unformatted list.
 * 
 * see template_preprocess_views_view_unformatted in views/theme/theme.inc
 */
function BootstrapBlocks_preprocess_views_view_unformatted(&$vars) {
  $view = $vars['view'];
  $rows = $vars['rows'];
  $style = $view->style_plugin;
  $options = $style->options;

  $vars['classes_array'] = array();
  $vars['classes'] = array();
  $default_row_class = isset($options['default_row_class']) ? $options['default_row_class'] : FALSE;
  $row_class_special = isset($options['row_class_special']) ? $options['row_class_special'] : FALSE;
  // Set up striping values.
  $count = 0;
  $max = count($rows);
  foreach ($rows as $id => $row) {
    $count++;
    if ($default_row_class) {
      $vars['classes'][$id][] = 'views-row';
      //$vars['classes'][$id][] = 'views-row-' . $count;
    }
    if ($row_class_special) {
      //$vars['classes'][$id][] = 'row-' . ($count % 2 ? 'odd' : 'even');
      if ($count == 1) {
        $vars['classes'][$id][] = 'views-row-first';
      }
      if ($count == $max) {
        $vars['classes'][$id][] = 'views-row-last';
      }
    }

    if ($row_class = $view->style_plugin->get_row_class($id)) {
      $vars['classes'][$id][] = $row_class;
    }

    // Flatten the classes to a string for each row for the template file.
    $vars['classes_array'][$id] = isset($vars['classes'][$id]) ? implode(' ', $vars['classes'][$id]) : '';
  }
}

/**
 * Display the view as an HTML list element
 */
function BootstrapBlocks_preprocess_views_view_list(&$vars) {
  $handler  = $vars['view']->style_plugin;

  $class = explode(' ', $handler->options['class']);
  $class = array_map('views_clean_css_identifier', $class);

  $wrapper_class = explode(' ', $handler->options['wrapper_class']);
  $wrapper_class = array_map('views_clean_css_identifier', $wrapper_class);

  $vars['class'] = implode(' ', $class);
  $vars['wrapper_class'] = implode(' ', $wrapper_class);
  $vars['wrapper_prefix'] = '';
  $vars['wrapper_suffix'] = '';
  $vars['list_type_prefix'] = '<' . $handler->options['type'] . '>';
  $vars['list_type_suffix'] = '</' . $handler->options['type'] . '>';
  if ($vars['wrapper_class']) {
    $vars['wrapper_prefix'] = '<div class="' . $vars['wrapper_class'] . '">';
    $vars['wrapper_suffix'] = '</div>';
  }

  if ($vars['class']) {
    $vars['list_type_prefix'] = '<' . $handler->options['type'] . ' class="' . $vars['class'] . '">';
  }
  BootstrapBlocks_preprocess_views_view_unformatted($vars);
}