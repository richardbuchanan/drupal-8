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

use Drupal\block\Entity\Block;
use Drupal\rcb\RCB;
use Drupal\rcb\RCBNodeImage;

/**
 * Implements template_preprocess_html().
 */
function rcb_preprocess_html(&$variables) {
  $variables['html_attributes']->addClass('uk-height-1-1');
}

/**
 * Implements template_preprocess_page().
 */
function rcb_preprocess_page(&$variables) {
  $node = isset($variables['node']) ? $variables['node'] : FALSE;
  $fid = $node && isset($node->field_image->entity) ? $node->field_image->entity->id() : NULL;
  $variables['node_image'] = RCBNodeImage::buildResponsiveImage($fid, 'wide');
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
 * Implements template_preprocess_block().
 */
function rcb_preprocess_block(&$variables) {
  $base_plugin_id = $variables['base_plugin_id'];
  $book_navigation = $base_plugin_id == 'book_navigation';
  $system_powered_by_block = $base_plugin_id == 'system_powered_by_block';

  $block = Block::load($variables['elements']['#id']);
  $region = $block->getRegion();

  switch ($region) {
    case 'footer':
      if ($system_powered_by_block) {
        $system_powered_by_content = RCB::systemPoweredByContent();
        $variables['content'] = $system_powered_by_content;
      }
      break;

    case 'offcanvas':
    case 'sidebar_second':
      if ($book_navigation) {
        $variables['content']['#theme'] = 'book_all_books_block__' . $region;
      }
      break;
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
 * Implements hook_preprocess_HOOK() for book-all-books-block.html.twig.
 */
function rcb_preprocess_book_all_books_block(&$variables) {
  $theme_original_hook = $variables['theme_hook_original'];
  $theme_hook = str_replace('book_all_books_block__', '', $theme_original_hook);
  $variables['book_menus'][0]['menu']['#theme'] = 'book_tree__' . $theme_hook;
}

/**
 * Implements hook_preprocess_HOOK() for book-tree.html.twig.
 */
function rcb_preprocess_book_tree(&$variables) {
  $theme_hook_original = $variables['theme_hook_original'];
  $sidebar_second_book_tree = $theme_hook_original == 'book_tree__sidebar_second';
  $offcanvas_book_tree = $theme_hook_original == 'book_tree__offcanvas';

  if ($sidebar_second_book_tree || $offcanvas_book_tree) {
    // Create copy of parent for first menu level.
    $items = $variables['items'];
    reset($items);
    $header = key($items);
    $nav_header = $items[$header];

    // Create copy of parent below for the first menu level.
    $header_below_items = $nav_header['below'];

    // Setup the new copy of parent for first menu level.
    $nav_header['below'] = [];
    $nav_header['attributes']->addClass('uk-nav-header');

    // Add copy of first parent as nav header.
    $variables['items'] = [
      $nav_header
    ];

    // Add copy of each parent below item.
    foreach ($header_below_items as $key => $new_item) {
      $variables['items'][$key] = $new_item;
    }
  }
}

/**
 * Implements template_preprocess_container().
 */
function rcb_preprocess_container(&$variables) {
  $filter_wrapper = in_array('filter-wrapper', $variables['attributes']['class']);
  $anonymous_user = \Drupal::currentUser()->isAnonymous();

  if ($filter_wrapper && $anonymous_user) {
    $variables['attributes']['class'][] = 'uk-hidden';
  }
}

/**
 * Implements hook_preprocess_HOOK() for feed-icon.html.twig.
 */
function rcb_preprocess_feed_icon(&$variables) {
  $variables['is_front'] = \Drupal::service('path.matcher')->isFrontPage();
}

/**
 * Implements template_preprocess_form_element().
 */
function rcb_preprocess_form_element(&$variables) {
  switch ($variables['type']) {
    case 'item':
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
  $type = $variables['attributes']['type'];
  $submit = $type == 'submit';
  $text_inputs = $type != 'checkbox' & $type != 'radio' && $type != 'range' && $type != 'submit';
  $variables['size_modifier'] = FALSE;

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

  if ($text_inputs) {
    $size = $variables['attributes']['size'];

    if ($size > 0) {
      $variables['size_modifier'] = 'uk-form-width-large';
    }
    else {
      $variables['size_modifier'] = 'uk-form-width-medium';
    }
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
 * Implements template_preprocess_user().
 */
function rcb_preprocess_user(&$variables) {
  $created = $variables['elements']['#user']->getCreatedTime();
  $member_for = \Drupal::service('date.formatter')->formatInterval(\Drupal::time()->getRequestTime() - $created);
  $variables['content']['member_for']['#markup'] = t('<p><strong>Member for</strong> @member_for</p>', ['@member_for' => $member_for]);
}
