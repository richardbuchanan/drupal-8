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

use Drupal\Core\Form\FormStateInterface;

/**
 * Implemnts hook_form_FORM_ID_alter() for search_block_form.
 */
function rcb_form_search_block_form_alter(&$form, FormStateInterface $form_state, $form_id) {
  $form['actions']['submit']['#attributes']['id'] = 'edit-submit--search-block-form';

  if ($form['form_id']['#id'] == 'edit-search-block-form') {
    $form['actions']['submit']['#theme_wrappers'] = ['input__search__search_block_form'];
  }
  else {
    $form['actions']['submit']['#theme_wrappers'] = ['input__search__search_block_form__mobile'];
    $form['#id'] = 'search-block-form--mobile';
  }

  $form['keys']['#attributes']['id'] = 'edit-keys--search-block-form';
  $form['keys']['#attributes']['placeholder'] = t('Search');
}
