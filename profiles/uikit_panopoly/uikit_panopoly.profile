<?php

/**
 * @file
 * Enables modules and site configuration for a UIkit Panopoly installation.
 */

use Drupal\Core\Form\FormStateInterface;

/**
 * Implements hook_form_FORM_ID_alter() for install_configure_form().
 *
 * Allows the profile to alter the site configuration form.
 */
function uikit_panopoly_form_install_configure_form_alter(&$form, FormStateInterface $form_state) {
  include_once drupal_get_path('profile', 'panopoly') . '/panopoly.profile';
  panopoly_form_install_configure_form_alter($form, $form_state);
}
