<?php

/**
 * @file
 * Set up variables to be placed within the template (.html.twig) files.
 *
 * The variables set up here apply to both templates (.html.twig) files and
 * functions (theme_HOOK). These are also used for providing
 * @link https://www.drupal.org/node/2354645 Twig Template naming conventions @endlink.
 *
 * @see process.inc
 */

use Drupal\Core\Template\Attribute;

/**
 * Implements template_preprocess_page().
 */
function bdg_preprocess_page(&$variables) {
  $variables['page_wrapper_attributes'] = new Attribute();
  $variables['page_wrapper_attributes']->setAttribute('id', 'page-wrapper');

  $variables['page_attributes'] = new Attribute();
  $variables['page_attributes']->setAttribute('id', 'page');
  $variables['page_attributes']->addClass('uk-container');
  $variables['page_attributes']->addClass('uk-container-expand');
  $variables['page_attributes']->addClass('uk-padding-small');
  $variables['page_attributes']->addClass('uk-padding-remove-top');
  $variables['page_attributes']->addClass('uk-padding-remove-bottom');

  $variables['footer_top_attributes'] = new Attribute();
  $variables['footer_top_attributes']->setAttribute('id', 'page-footer-top');
  $variables['footer_top_attributes']->addClass('uk-padding-small');
  $variables['footer_top_attributes']->addClass('uk-container-expand');
  $variables['footer_top_attributes']->addClass('uk-padding-small');

  $variables['footer_bottom_attributes'] = new Attribute();
  $variables['footer_bottom_attributes']->setAttribute('id', 'page-footer-bottom');
  $variables['footer_bottom_attributes']->addClass('uk-padding-small');
  $variables['footer_bottom_attributes']->addClass('uk-container-expand');
  $variables['footer_bottom_attributes']->addClass('uk-padding-small');
}

/**
 * Implements template_preprocess_input().
 */
function bdg_preprocess_input(&$variables) {
  if ($variables['element']['#type'] == 'submit') {
    $variables['attributes']['class'][] = 'uk-button';
    $value = $variables['element']['#value']->__toString();

    switch ($value) {
      case 'Log in':
      case 'Preview':
      case 'Send message':
      case 'Submit':
        $variables['attributes']['class'][] = 'uk-button-primary';
        break;

      default:
        $variables['attributes']['class'][] = 'uk-button-default';
    }
  }
}

/**
 * Implements template_preprocess_block().
 */
/* -- Delete this line if you want to use this function
function bdg_preprocess_block(&$variables) {
}
// */

/**
 * Implements template_preprocess_breadcrumb().
 */
/* -- Delete this line if you want to use this function
function bdg_preprocess_breadcrumb(&$variables) {
}
// */

/**
 * Implements template_preprocess_details().
 */
/* -- Delete this line if you want to use this function
function bdg_preprocess_details(&$variables) {
}
// */

/**
 * Implements hook_preprocess_HOOK() for feed-icon.html.twig.
 */
/* -- Delete this line if you want to use this function
function bdg_preprocess_feed_icon(&$variables) {
}
// */

/**
 * Implements template_preprocess_form_element().
 */
/* -- Delete this line if you want to use this function
function bdg_preprocess_form_element(&$variables) {
}
// */

/**
 * Implements template_preprocess_form_element() for form-element--advanced.html.twig.
 */
/* -- Delete this line if you want to use this function
function bdg_preprocess_form_element__advanced(&$variables) {
}
// */

/**
 * Implements template_preprocess_links() for links--dropbutton.html.twig.
 */
/* -- Delete this line if you want to use this function
function bdg_preprocess_links__dropbutton(&$variables) {
}
// */

/**
 * Implements template_preprocess_menu_local_action().
 */
/* -- Delete this line if you want to use this function
function bdg_preprocess_menu_local_action(&$variables) {
}
// */

/**
 * Implements hook_preprocess_HOOK() for menu-local-tasks.html.twig.
 */
/* -- Delete this line if you want to use this function
function bdg_preprocess_menu_local_tasks(&$variables) {
}
// */

/**
 * Implements hook_preprocess_HOOK() for menu--navbar.html.twig
 */
/* -- Delete this line if you want to use this function
function bdg_preprocess_menu__navbar(&$variables) {
}
// */

/**
 * Implements hook_preprocess_HOOK() for menu--offcanvas.html.twig
 */
/* -- Delete this line if you want to use this function
function bdg_preprocess_menu__offcanvas(&$variables) {
}
// */
