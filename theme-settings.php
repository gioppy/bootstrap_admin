<?php

function bootstrap_admin_form_system_theme_settings_alter(&$form, $form_state, $form_id = NULL) {
  // Work-around for a core bug affecting admin themes. See issue #943212.
  if (isset($form_id)) {
    return;
  }

  $form['bootstrap_themes'] = array(
    '#type'          => 'fieldset',
    '#title'         => t('Bootstrap Theme'),
  );

  $form['bootstrap_themes']['theme'] = array(
    '#type' => 'select',
    '#title' => t('Themes'),
    '#description' => t('Themes from !url', array('!url' => l('Bootswatch', "http://bootswatch.com/"))),
    '#options' => array(
      'default' => 'Default',
      'amelia' => 'Amelia',
      'cerulean' => 'Cerulean',
      'cosmo' => 'Cosmo',
      'cyborg' => 'Cyborg',
      'flatly' => 'Flatly',
      'journal' => 'Journal',
      'readable' => 'Readable',
      'simplex' => 'Simplex',
      'slate' => 'Slate',
      'spacelab' => 'Spacelab',
      'united' => 'United',
      'yeti' => 'Yeti',
    ),
    '#default_value' => theme_get_setting('theme'),
  );

}

