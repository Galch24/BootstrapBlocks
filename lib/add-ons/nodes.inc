<?php

function BootstrapBlocks_get_field_view($node, $field_name, $delta = FALSE, $caret = FALSE) {
  $output = '';
  
  if ($delta) {
    $field = field_view_value('node', $node, $field_name, $field[$delta]);
    $output = drupal_render($field);
  }
  else {
    $field = field_get_items('node', $node, $field_name);
    $output = drupal_render(field_view_field('node', $node, $field_name, array('label' => 'hidden')));
  } 
  
  return $output;
}

/*
 *  http://habrahabr.ru/post/163501/
 */
function BootstrapBlocks_get_fields_view($node) {
  
  $fields = array();
  // Get names of the fields. Notes: field object is always array?
  foreach ($node as $id => $node_field) {
    if (is_array($node_field)) {
      $fields[$id] = '';
    }
  }
  
  $items = array();
  foreach ($fields as $fname => $field) {
    $field = field_get_items('node', $node, $fname);
    $items[$fname] = drupal_render(field_view_field('node', $node, $fname));
  }
 
  //print '<pre>$data = '. check_plain(print_r($items, 1)) .'</pre>';    
}