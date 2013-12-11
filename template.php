<?php

/**
 * @file template.php
 */

// Provide < PHP 5.3 support for the __DIR__ constant.
define('_DIR_', dirname(__FILE__));
require_once _DIR_ . '/includes/form.inc';
require_once _DIR_ . '/includes/block.inc';

/**
 * Implements hook_preprocess_page().
 */
function bootstrap_admin_preprocess_page(&$variables){
  $themes = theme_get_setting('theme');
  if($themes != 'default'){
    drupal_add_css(path_to_theme() . '/themes/' . $themes . '/bootstrap.min.css', array('group' => CSS_THEME, 'weight' => 100));
  }
  // Only display the shortcut link if the user has the ability to edit
  // shortcuts and if the page's actual content is being shown (for example,
  // we do not want to display it on "access denied" or "page not found"
  // pages).
  if (shortcut_set_edit_access() && ($item = menu_get_item()) && $item['access']) {
    if (theme_get_setting('shortcut_module_link')) {
      $shortcut_link = $variables['title_suffix']['add_or_remove_shortcut'];
      $link_text = strip_tags($shortcut_link['#title'], '<em>');
      $link_path = $shortcut_link['#href'];
      $query = $shortcut_link['#options']['query'];
      
      unset($variables['title_suffix']['add_or_remove_shortcut']['#attached']['css']);
      
      $variables['title_suffix']['add_or_remove_shortcut'] = array(
        '#prefix' => '<div class="add-or-remove-shortcuts"><div class="btn-group dropup"><button class="btn btn-primary btn-mini">' . t('Add shortcut') . '</button><button class="btn dropdown-toggle btn-primary btn-mini" data-toggle="dropdown"><span class="caret"></span></button>',
        '#type' => 'markup',
        '#markup' => '<ul class="dropdown-menu"><li>' . l($link_text, $link_path, array('query' => $query, 'html' => TRUE)) . '</li></ul>',
        '#suffix' => '</div></div>',
      );
    }
  }
}