<?php

/**
 * Preprocessor for theme('button').
 */
function bootstrap_admin_theme_preprocess_button(&$vars) {
  $vars['element']['#attributes']['class'][] = 'btn';

  if (isset($vars['element']['#value'])) {
    $classes = array(
      //specifics
      t('Cancel') => 'btn-danger',
    );
    foreach ($classes as $search => $class) {
      if (strpos($vars['element']['#value'], $search) !== FALSE) {
        $vars['element']['#attributes']['class'][] = $class;
        break;
      }
    }
  }
}

/**
 * Returns HTML for a button form element.
 */
function bootstrap_admin_theme_button($variables) {
  $element = $variables['element'];
  $label = $element['#value'];
  element_set_attributes($element, array('id', 'name', 'value', 'type'));

  $element['#attributes']['class'][] = 'form-' . $element['#button_type'];
  if (!empty($element['#attributes']['disabled'])) {
    $element['#attributes']['class'][] = 'form-button-disabled';
  }

  // Prepare input whitelist - added to ensure ajax functions don't break
  $whitelist = _bootstrap_element_whitelist();
  
  return '<input' . drupal_attributes($element['#attributes']) . ">\n"; // This line break adds inherent margin between multiple buttons
}

/**
 * Returns HTML for a form element.
 */
function bootstrap_admin_theme_form_element(&$variables) {
  $element = &$variables['element'];

  // This function is invoked as theme wrapper, but the rendered form element
  // may not necessarily have been processed by form_builder().
  $element += array(
    '#title_display' => 'before',
  );

  // Add element #id for #type 'item'.
  if (isset($element['#markup']) && !empty($element['#id'])) {
    $attributes['id'] = $element['#id'];
  }
  // Add element's #type and #name as class to aid with JS/CSS selectors.
  $attributes['class'] = array('form-item');
  if (!empty($element['#type'])) {
    $attributes['class'][] = 'form-type-' . strtr($element['#type'], '_', '-');
  }
  if (!empty($element['#name'])) {
    $attributes['class'][] = 'form-item-' . strtr($element['#name'], array(' ' => '-', '_' => '-', '[' => '-', ']' => ''));
  }
  // Add a class for disabled elements to facilitate cross-browser styling.
  if (!empty($element['#attributes']['disabled'])) {
    $attributes['class'][] = 'form-disabled';
  }
  $output = '<div' . drupal_attributes($attributes) . '>' . "\n";

  // If #title is not set, we don't display any label or required marker.
  if (!isset($element['#title'])) {
    $element['#title_display'] = 'none';
  }
  $prefix = isset($element['#field_prefix']) ? '<span class="field-prefix">' . $element['#field_prefix'] . '</span> ' : '';
  $suffix = isset($element['#field_suffix']) ? ' <span class="field-suffix">' . $element['#field_suffix'] . '</span>' : '';

  switch ($element['#title_display']) {
    case 'before':
    case 'invisible':
      $output .= ' ' . theme('form_element_label', $variables);
      $output .= ' ' . $prefix . $element['#children'] . $suffix . "\n";
      break;

    case 'after':
      $output .= ' ' . $prefix . $element['#children'] . $suffix;
      $output .= ' ' . theme('form_element_label', $variables) . "\n";
      break;

    case 'none':
    case 'attribute':
      // Output no label and no required marker, only the children.
      $output .= ' ' . $prefix . $element['#children'] . $suffix . "\n";
      break;
  }

  if (!empty($element['#description'])) {
    $output .= '<div class="description">' . $element['#description'] . "</div>\n";
  }

  $output .= "</div>\n";

  return $output;
}

/**
 * Returns HTML for a CTOOLS dropbutton element.
 */
function bootstrap_admin_theme_links__ctools_dropbutton($vars){
  // Check to see if the number of links is greater than 1;
  // otherwise just treat this like a button.
  if (!empty($vars['links'])) {
    $is_drop_button = (count($vars['links']) > 1);
    // Add needed files
    if ($is_drop_button) {
      ctools_add_js('dropbutton');
      ctools_add_css('dropbutton');
    }
    // Provide a unique identifier for every button on the page.
    static $id = 0;
    $id++;
    
    // Wrapping div
    $class = 'ctools-no-js';
    $class .= ($is_drop_button) ? ' btn-group' : '';
    $class .= ' ctools-button';
    if (!empty($vars['class'])) {
      $class .= ($vars['class']) ? (' ' . implode(' ', $vars['class'])) : '';
    }

    $output = '';

    $output .= '<div class="' . $class . '" id="ctools-button-' . $id . '">';
    
    $vars['title'] = ($vars['title'] ? check_plain($vars['title']) : t('actions'));

    // Add a twisty if this is a dropbutton
    if ($is_drop_button) {
      if ($vars['image']) {
        //TODO: image button?
        $output .= '<a href="#" class="ctools-twisty ctools-image">' . $vars['title'] . '</a>';
      }
      else {
        $output .= '<a class="btn btn-mini btn-info dropdown-toggle" data-toggle="dropdown" href="#">' . $vars['title'] . '<span class="caret"></span></a>';
      }
    }else{
      $output .= '<a class="btn btn-mini btn-info dropdown-toggle" data-toggle="dropdown" href="#">' . $vars['title'] . '<span class="caret"></span></a>';
    }

    // Check for attributes. theme_links expects an array().
    $vars['attributes'] = (!empty($vars['attributes'])) ? $vars['attributes'] : array();

    // Remove the inline and links classes from links if they exist.
    // These classes are added and styled by Drupal core and mess up the default
    // styling of any link list.
    if (!empty($vars['attributes']['class'])) {
      $classes = $vars['attributes']['class'];
      foreach ($classes as $key => $class) {
        if ($class === 'inline' || $class === 'links') {
          unset($vars['attributes']['class'][$key]);
        }
      }
    }
    
    $vars['attributes']['class'][] = 'dropdown-menu';

    // Call theme_links to render the list of links.
    $output .= theme_links(array('links' => $vars['links'], 'attributes' => $vars['attributes'], 'heading' => ''));
    $output .= '</div>'; // ctools-dropbutton
    return $output;
  }else{
    return '';
  }
}

/**
 * Returns HTML for a marker for new or updated content.
 */
function bootstrap_admin_theme_mark($variables){
  $type = $variables['type'];
  global $user;
  if ($user->uid) {
    if ($type == MARK_NEW) {
      return ' <span class="label label-success">' . t('new') . '</span>';
    }
    elseif ($type == MARK_UPDATED) {
      return ' <span class="label label-info">' . t('updated') . '</span>';
    }
  }
}

/**
 * Implement hook_field_group_pre_render_alter.
 */
function bootstrap_admin_theme_field_group_pre_render_alter(&$element, $group, &$form) {
  if($group->format_type == 'htab'){
    $element['#attributes']['class'][] = 'tab-pane';
  }
}

/**
 * Returns HTML for an element's children fieldsets as horizontal tabs.
 */
function bootstrap_admin_theme_horizontal_tabs($variables) {
  $element = $variables['element'];
  // Add required JavaScript and Stylesheet.
  $element['#attached']['library'][] = array('field_group', 'horizontal-tabs');

  $output = '<h2 class="element-invisible">' . (!empty($element['#title']) ? $element['#title'] : t('Horizontal Tabs')) . '</h2>';
  $output .= '<div class="horizontal-tabs-panes tab-content">' . $element['#children'] . '</div>';

  return $output;
}
