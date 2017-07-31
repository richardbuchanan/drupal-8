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

use Drupal\Core\Template\Attribute;
use Drupal\block\Entity\Block;

/**
 * Implements hook_theme_suggestions_HOOK_alter().
 */
function rcb_theme_suggestions_block_alter(array &$suggestions, array $variables) {
  $block_id = $variables['elements']['#id'];
  $block = Block::load($block_id);
  $region = $block->getRegion();
  $suggestions[] = 'block__' . $region . '__' . $block_id;
}

/**
 * Implements hook_form_FORM_ID_alter() for comment_form().
 */
function rcb_form_comment_form_alter(&$form, \Drupal\Core\Form\FormStateInterface $form_state, $form_id) {
  if (\Drupal::currentUser()->isAnonymous()) {
    $form['author']['name']['#required'] = TRUE;
    $form['author']['mail']['#required'] = TRUE;
    $form['author']['homepage']['#access'] = FALSE;
  }
}

/**
 * Implements hook_form_FORM_ID_alter() for user_login_form().
 */
function rcb_form_user_login_form_alter(&$form, \Drupal\Core\Form\FormStateInterface $form_state, $form_id) {
  $form['actions']['#attributes'] = new Attribute;
  $form['actions']['#attributes']->addClass('uk-display-inline-block');
  $form['actions']['#attributes']->addClass('uk-width-1-1');
}
