<?php
/**
 * Implement hook_block_view_MODULE_DELTA_alter().
 */
function bootstrap_admin_theme_block_view_locale_language_alter(&$data, $block){
  $path = drupal_is_front_page() ? '<front>' : $_GET['q'];
  $links = language_negotiation_get_switch_links($block->delta, $path);
  
  foreach($links->links as $link){
    $links->links[$link['language']->language]['attributes']['class'] = array('language-link', 'btn', 'btn-info', 'btn-mini');
  }
  $class = "language-switcher-{$links->provider}";
  $variables = array('links' => $links->links, 'attributes' => array('class' => array($class)));
  $data['content'] = theme('links__locale_block', $variables);
}