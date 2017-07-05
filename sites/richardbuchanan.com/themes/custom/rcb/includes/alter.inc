<?php

/**
 * @file
 * Modify structured content arrays.
 *
 * These hooks are called after the content has been assembled in a structured
 * array and may be used for doing processing which requires that the complete
 * content structure has been built.
 *
 * If the theme wishes to act on the rendered HTML of the content rather than
 * the structured content array, it may use this hook to add a #post_render
 * callback. Alternatively, it could also implement hook_preprocess_HOOK().
 *
 * @see \Drupal\Core\Render\RendererInterface
 * @see \Drupal\Core\Render\Renderer
 */

/**
 * Implements hook_theme_suggestions_HOOK_alter() for container templates.
 */
function rcb_theme_suggestions_container_alter(array &$suggestions, array $variables) {
  $type = isset($variables['element']['#type']) ? $variables['element']['#type'] : 0;

  if ($type && $type != 'container') {
    $submit = isset($variables['element']['submit']);
    $submit_value = $submit && isset($variables['element']['submit']['#value']) ? $variables['element']['submit']['#value']->getUntranslatedString() : 0;

    if ($submit_value && $submit_value != 'Search') {
      $suggestions[] = "container__$type";
    }
    else {
      $suggestions[] = "container__$type" . '__search';
    }
  }

  if (isset($variables['element']['administration_menu'])) {
    $suggestions[] = 'container__admin__toolbar';
  }
}

/**
 * Implements hook_theme_suggestions_HOOK_alter() for form element templates.
 */
function rcb_theme_suggestions_form_element_alter(array &$suggestions, array $variables) {
  $type = $variables['element']['#type'];
  $parents = isset($variables['element']['#array_parents']) ? $variables['element']['#array_parents'] : [];
  $key = array_search('form_element__search', $suggestions);

  if ($type == 'search' && $parents && !in_array('basic', $parents) && $key !== false) {
    unset($suggestions[$key]);
  }
}
