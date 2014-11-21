<?php

/*
 * Extensions for module Data https://www.drupal.org/node/1658784
 * 
 */

function BootstrapBlocks_views_data_alter(&$views) {
  // name of the database view
  $dbview_name = 'webform_views___';
  $pseudo_pk = 'sid';
  _mysql_views_designate_primarykey($dbview_name, $pseudo_pk, $views);
}