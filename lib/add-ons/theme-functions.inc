<?php
/*
 * Return list for options of the checkbox group 
 * @return
 *   Html $output.
 */
function BootstrapBlocks_checkbox_list($vid, $parent = 0, $max_depth = NULL, $load_entities = FALSE,$name=false) {
  $items = array();
  
  $terms = taxonomy_get_tree($vid, $parent, $max_depth, $load_entities);
  $count = count($terms);
  $columns = 3;
  $output = '<div class="col-sm-4">';
  $i = 1;
  foreach ($terms as $id => $term) {
    //$items[$term->tid] = $term->name;
    if (!$name)
		$output .= '<div class="checkbox"><label><input value="'.$term->tid.'"id="type_'.$term->tid.'" type="checkbox">'.$term->name.'<span></span></label></div>';
    else
		$output .= '<div class="checkbox"><label><input value="'.$term->tid.'"id="type_'.$term->tid.'" type="checkbox" name="'.$name.'">'.$term->name.'<span></span></label></div>';
    if (($i % (($count / $columns) + 1)) == 0 ) {
      $output .= '</div><div class="col-sm-4">';
    }
    $i = $i + 1;
  }
  $output .= '</div>';
  if  ($i == 1) $output=null;
  //print '<pre>$count = '. check_plain(print_r($output, 1)) .'</pre>';
  return $output;
}

/*
 * Return options for select
 * @return
 *   Html $output.
 */
function BootstrapBlocks_option_list($vid, $parent = 0, $max_depth = NULL, $load_entities = FALSE) {
  
  $terms = taxonomy_get_tree($vid, $parent, $max_depth, $load_entities);
  $output = '';
  foreach ($terms as $id => $term) {    
    $parents = taxonomy_get_parents_all($term->tid);          
    $output .= '<option class="'.'opt-' . count($parents).'" value="'.$term->tid.'">'.$term->name.'</option>';  
  }

  //print '<pre>$term = '. check_plain(print_r(count($term->parents), 1)) .'</pre>';
  return $output;
}

/*
 * Return options for select
 * @return
 *   Html $output.
 */
function BootstrapBlocks_button_list($vid, $parent = 0, $max_depth = NULL, $prefix = 'cat',$onclick = false) {
  
  $terms = taxonomy_get_tree($vid, $parent, $max_depth);
  $output = '<input id="'.$prefix.'" name="'.$prefix.'[]" value="3" type="hidden"/>';
  $active="active";
  foreach ($terms as $id => $term) {
    if ($onclick) {
      $onclick="select_type ('".$prefix.'-'.$term->tid."');";
    }
    else {
      $onclick = false;
    }
    
    $output .= '<a  class="btn btn-info '.$prefix.' '.$active.'" id="'.$prefix.'-'.$term->tid."\" onClick=\"change_form_value ('".$prefix."',".$term->tid.");".$onclick."\">".$term->name.'</a>'; 
    $active="";
    }

  //print '<pre>$count = '. check_plain(print_r($output, 1)) .'</pre>';
  return $output;
}

function BootstrapBlocks_button_list_geo($vid, $parent = 0, $max_depth = NULL ) {
  $prefix = 'geo';
  $output ='';
  $terms = taxonomy_get_tree($vid, $parent, $max_depth);
  
  foreach ($terms as $id => $term) {
    $output .= '<a class="btn btn-info" id="'.$prefix.'-'.$term->tid."\" onClick=\"change_form_value_geo (".$term->tid.")\">".$term->name.'</a>'; 
  }

  //print '<pre>$count = '. check_plain(print_r($output, 1)) .'</pre>';
  return $output;
}

/*
 * Return options for select
 * @return
 *   Html $output.
 */
function BootstrapBlocks_atab_list($vid, $parent = 0, $max_depth = NULL, $prefix = 'cat') {
  
  $terms = taxonomy_get_tree($vid, $parent, $max_depth);
  $output = '';
  foreach ($terms as $id => $term) {
    $output .= '<a class="btn btn-info" id="'.$prefix.'-'.$term->tid.'">'.$term->name.'</a>'; 
  }

  //print '<pre>$count = '. check_plain(print_r($output, 1)) .'</pre>';
  return $output;
}

/*
 * Return field output
 * @return
 *   Html $output.
$node = node_load($nid);
$field = field_get_items('node', $node, 'field_name');
$output = field_view_value('node', $node, 'field_name', $field[$delta]);
 */
function BootstrapBlocks_field_output($node, $field_name, $type = 'node', $delta = 0) {
  $field = field_get_items('node', $node, $field_name);
  
  // Get the field type
  $render = field_view_field('node', $node, $field_name);
  $field_type = $render['#field_type'];
  
  $output = 0;
  
  // Single value for field with number or text type
  if ($delta == 0) {    
    $output = $field[$delta]['value'];
    
    if (($field_type == 'list_integer') || ($field_type == 'number_integer')) {
      $output = number_format($output, 0, ',', ' ');
    }   
    elseif ($field_type == 'number_float') {
      //$output = field_view_field('node', $node, $field_name);
      $output = number_format($output, 0, ',', ' ');
      
      
    }
    //print '<pre>$render = '. check_plain(print_r($render, 1)) .'</pre>';
  }
  
  return $output;
}

/* 
 * Выводит всех родителей термина, включая сам термин, в качестве ссылок.
 * 
 * TODO: Если несколько значений у поля, то нужно убрать дубли. 
 *       Пока выводит родителей только для первого значения поля.
 */

function BootstrapBlocks_get_field_parents($node, $field_name) {
  $field_terms = field_get_items('node', $node, $field_name);
  $term_parents = array();
  foreach ($field_terms as $id => $term) {
    $term_parents[] = taxonomy_get_parents_all($term['tid']);
  }
  $output = '';
  foreach ($term_parents[0] as $id => $term_parent) {
    $output .= '<div class="f-item">';
    $output .= l($term_parent->name, drupal_get_path_alias('taxonomy/term/'.$term_parent->tid));
    $output .= '</div>';
  }
  //print '<pre>$geo_parents = '. check_plain(print_r($output, 1)) .'</pre>';
  return $output;
}


