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
function rcb_preprocess_page(&$variables) {
  $variables['header_attributes']->removeAttribute('uk-sticky');
  $variables['header_attributes']->removeAttribute('media');
  $variables['navbar_attributes']->addClass('uk-navbar-transparent');

  $variables['page_title_attributes'] = new Attribute;
  $variables['page_title_attributes']->setAttribute('id', 'page--title');
  $variables['page_title_attributes']->addClass('uk-width-1-1');

  $variables['search_bar_attributes'] = new Attribute;
  $variables['search_bar_attributes']->setAttribute('id', 'search--bar');
  $variables['search_bar_attributes']->addClass('uk-width-1-1');
}

/**
 * Implements template_preprocess_block().
 */
function rcb_preprocess_block(&$variables) {
  if ($variables['plugin_id'] == 'system_main_block') {
    $variables['attributes']['class'][] = 'uk-margin-top';
  }
}

/**
 * Implements template_preprocess_breadcrumb().
 */
function rcb_preprocess_breadcrumb(&$variabes) {
  $current_path = \Drupal::service('path.current')->getPath();

  if ($current_path == '/search/content' || $current_path == '/search/content/help') {
    unset($variabes['breadcrumb'][0]);
  }
}

/**
 * Implements template_preprocess_node().
 */
function rcb_preprocess_node(&$variables) {
  $timestamp = $variables['node']->getCreatedTime();
  $date = \Drupal::service('date.formatter')->format($timestamp, $type = 'short');
  $variables['date'] = $date;

  if (!$variables['teaser']) {
    $nid = $variables['node']->id();

    $comment_attributes = new Attribute;
    $comment_attributes->setAttribute('id', "#article--comments-$nid");

    $meta_attributes = new Attribute;
    $meta_attributes->addClass('uk-article-meta');
    $meta_attributes->addClass('uk-article-meta--full-node');
    $meta_attributes->addClass('uk-float-left');
    $meta_attributes->addClass('uk-margin-right');

    $variables['attributes']['id'] = "article--node-$nid";
    $variables['comment_attributes'] = $comment_attributes;
    $variables['content_attributes']['class'][] = 'node--content';
    $variables['content_attributes']['class'][] = 'uk-margin-small-top';
    $variables['meta_attributes'] = $meta_attributes;
  }
}

/**
 * Implements template_preprocess_field().
 */
function rcb_preprocess_field(&$variables) {
  $entity = isset($variables['element']['#object']) ? $variables['element']['#object'] : [];
  $field_name = $variables['field_name'];

  if ($entity && $field_name == 'field_tags') {
    $variables['title_attributes']['class'][] = 'uk-text-bold';
    $variables['title_attributes']['class'][] = 'uk-margin-remove-bottom';
    $variables['title_attributes']['class'][] = 'uk-margin-small-top';
  }
}
