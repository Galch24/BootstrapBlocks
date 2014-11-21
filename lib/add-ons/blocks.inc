<?php

/**
 * Processes variables for block.tpl.php.
 *
 * Prepares the values passed to the theme_block function to be passed
 * into a pluggable template engine. Uses block properties to generate a
 * series of template file suggestions. If none are found, the default
 * block.tpl.php is used.
 *
 * Most themes utilize their own copy of block.tpl.php. The default is located
 * inside "modules/block/block.tpl.php". Look in there for the full list of
 * variables.
 *
 * The $variables array contains the following arguments:
 * - $block
 *
 * @see block.tpl.php
 */
function BootstrapBlocks_preprocess_block(&$variables) {


  $variables['classes_array'][1] = drupal_html_class($variables['block']->module);

  if ($variables['classes_array'][0] === 'block') {
    $variables['classes_array'][0] = '';
  }

  // Hyphens (-) and underscores (_) play a special role in theme suggestions.
  // Theme suggestions should only contain underscores, because within
  // drupal_find_theme_templates(), underscores are converted to hyphens to
  // match template file names, and then converted back to underscores to match
  // pre-processing and other function names. So if your theme suggestion
  // contains a hyphen, it will end up as an underscore after this conversion,
  // and your function names won't be recognized. So, we need to convert
  // hyphens to underscores in block deltas for the theme suggestions.
  
  // Create a valid HTML ID and make sure it is unique.
  $variables['block_html_id'] = drupal_html_id($variables['block']->module . '-' . $variables['block']->delta);
}
