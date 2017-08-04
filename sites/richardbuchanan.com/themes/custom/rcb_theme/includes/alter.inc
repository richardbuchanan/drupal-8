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

use Drupal\block\Entity\Block;
use Drupal\Core\Form\FormStateInterface;

/**
 * Implements hook_theme_suggestions_alter().
 */
function rcb_theme_theme_suggestions_alter(array &$suggestions, array $variables, $hook) {
  switch ($hook) {
    case 'block':
      $base_plugin_id = $variables['elements']['#base_plugin_id'];
      $block = Block::load($variables['elements']['#id']);
      $region = $block->getRegion();
      $suggestions[] = 'block__' . $region . '__' . $base_plugin_id;
      break;

    case 'form':
      $form_id = $variables['element']['#form_id'];
      $suggestions[] = 'form__' . $form_id;
      break;

    case 'menu':
      $menu_name = $variables['menu_name'];

      if ($variables['theme_hook_original'] != 'menu__offcanvas') {
        switch ($menu_name) {
          case 'account':
          case 'main':
          case 'tools':
            $suggestions[] = 'menu__nav';
            break;
        }
      }

      break;
  }
}

/**
 * Implements hook_form_FORM_ID_alter().
 */
function rcb_theme_form_search_block_form_alter(&$form, FormStateInterface $form_state, $form_id) {
  $form['actions']['submit']['#icon'] = 'search';
  $form['actions']['#attributes']['class'][] = 'uk-position-absolute';
}

/**
 * Implements hook_form_FORM_ID_alter().
 */
function rcb_theme_form_search_form_alter(&$form, FormStateInterface $form_state, $form_id) {
  $form['basic']['actions'] = [
    '#type' => 'actions',
    'submit' => $form['basic']['submit'],
  ];
  unset($form['basic']['submit']);
  $form['basic']['#attributes']['class'] = [];
}
