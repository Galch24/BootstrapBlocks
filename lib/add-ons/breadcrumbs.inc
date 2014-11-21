<?php

// Breadcrumbs override
function BootstrapBlocks_breadcrumb($variables) {
  $breadcrumb = $variables['breadcrumb'];
  $output     = '<span class="element-invisible">' . t('') . '</span>';
  
  if (!empty($breadcrumb)) {

    //print '<pre>$breadcrumb = '. check_plain(print_r($breadcrumb, 1)) .'</pre>';
    
    //$breadcrumb[] = drupal_get_title(); // Для добавления активного хвоста разкомментируйте
    // arrow = &nbsp; &rarr; &nbsp;
    $output .= '<div class="breadcrumb">' . implode('&nbsp; / &nbsp;', $breadcrumb) . '</div>';
    return $output;
  }
}



