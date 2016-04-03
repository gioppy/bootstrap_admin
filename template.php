<?php

/**
 * @file template.php
 */

// Provide < PHP 5.3 support for the __DIR__ constant.
define('_DIR_', dirname(__FILE__));
//require_once _DIR_ . '/includes/form.inc';
//require_once _DIR_ . '/includes/block.inc';

/**
 * Implements hook_preprocess_page().
 */
/*function bootstrap_admin_theme_preprocess_page(&$variables){
  // Only display the shortcut link if the user has the ability to edit
  // shortcuts and if the page's actual content is being shown (for example,
  // we do not want to display it on "access denied" or "page not found"
  // pages).
  if (module_exists('shortcut') && shortcut_set_edit_access() && ($item = menu_get_item()) && $item['access']) {
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

  if(module_exists('field_group')){
    drupal_add_js(drupal_get_path('theme', 'bootstrap_admin_theme') . '/js/horizontal-tabs.js');
  }
}*/

/**
 * Utility function for returning active languages
 *
 * @return HTML List
 */
function _bootstrap_admin_theme_set_languages(){
  if(drupal_multilingual() && module_exists('i18n')){
    $path = drupal_is_front_page() ? '<front>' : $_GET['q'];
    //get only language type
    $types = language_types_configurable(FALSE);
    $type = array_keys($types, 'language');
    $links = language_negotiation_get_switch_links($types[$type[0]], $path);

    if (isset($links->links)) {
      foreach($links->links as $link){
        $links->links[$link['language']->language]['attributes']['class'] = array('language-link', 'btn', 'btn-info', 'btn-mini');
      }
      $class = "language-switcher-{$links->provider}";
      $variables = array('links' => $links->links, 'attributes' => array('class' => array($class)));
      $output = theme('links__locale_block', $variables);
      return $output;
    }
  }else{
    return;
  }
}
