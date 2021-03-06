<?php
/**
 * @file
 * wsdot_project_pin_report_content_type.ds.inc
 */

/**
 * Implements hook_ds_layout_settings_info().
 */
function wsdot_project_pin_report_content_type_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|pin_report|default';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'pin_report';
  $ds_layout->view_mode = 'default';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'regions' => array(
      'ds_content' => array(
        0 => 'body',
      ),
    ),
    'fields' => array(
      'body' => 'ds_content',
    ),
    'classes' => array(),
    'wrappers' => array(
      'ds_content' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
    'layout_link_attribute' => '',
    'layout_link_custom' => '',
  );
  $export['node|pin_report|default'] = $ds_layout;

  return $export;
}
