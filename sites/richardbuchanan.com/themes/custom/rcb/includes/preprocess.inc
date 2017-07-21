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

/**
 * Implements template_preprocess_html().
 */
function rcb_preprocess_html(&$variables) {
  $user = \Drupal::currentUser();
  if ($user->hasPermission('access toolbar')) {
    $variables['html_attributes']->addClass('toolbar-fixed');
  }
}

/**
 * Implements template_preprocess_region().
 */
function rcb_preprocess_region(&$variables) {
  switch ($variables['region']) {
    case 'sidebar_first':
      $variables['attributes']['class'][] = 'uk-height-1-1';
      break;
  }
}

/**
 * Implements hook_preprocess_HOOK() for page-title.html.twig.
 */
function rcb_preprocess_page_title(&$variables) {
  if (($key = array_search('uk-text-center', $variables['title_attributes']['class'])) !== false) {
    unset($variables['title_attributes']['class'][$key]);
  }
}

/**
 * Implements template_preprocess_node().
 */
function rcb_preprocess_node(&$variables) {
  $timestamp = $variables['node']->getCreatedTime();
  $date = \Drupal::service('date.formatter')->format($timestamp, $type = 'short');
  $variables['date'] = $date;
}

/**
 * Implements template_preprocess_form_element().
 */
function rcb_preprocess_form_element(&$variables) {
  switch ($variables['type']) {
    case 'textarea':
      $variables['margin'] = FALSE;
      break;

    default:
      $variables['margin'] = TRUE;
  }
}

/**
 * Implements hook_preprocess_HOOK() for input.html.twig.
 */
function rcb_preprocess_input(&$variables) {
  $element = $variables['element'];
  $submit = isset($element['#type']) && $element['#type'] == 'submit';

  if ($submit) {
    // Add the uk-button class.
    $variables['attributes']['class'] = ['uk-button'];

    // Add uk-button-* classes based on the value of the button.
    $value = $element['#value']->render();
    switch ($value) {
      case 'Advanced search':
      case 'Create new account':
      case 'Log in':
      case 'Save':
      case 'Search':
      case 'Send message':
      case 'Submit':
        $variables['attributes']['class'][] = 'uk-button-primary';
        break;

      default:
        $variables['attributes']['class'][] = 'uk-button-default';
    }
  }
}
