<?php
/**
 * @file
 * wsdot_projects.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function wsdot_projects_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_project_metadata|node|project|form';
  $field_group->group_name = 'group_project_metadata';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'project';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'project_metadata',
    'weight' => '8',
    'children' => array(
      0 => 'field_cities',
      1 => 'field_counties',
      2 => 'field_funding_types',
      3 => 'field_highways',
      4 => 'field_link',
      5 => 'field_modes',
      6 => 'field_project_id',
      7 => 'field_regions',
      8 => 'field_tags',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-project-metadata field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_project_metadata|node|project|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_status|node|project|form';
  $field_group->group_name = 'group_status';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'project';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Status',
    'weight' => '1',
    'children' => array(
      0 => 'field_status_date',
      1 => 'field_status',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-status field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_status|node|project|form'] = $field_group;

  return $export;
}