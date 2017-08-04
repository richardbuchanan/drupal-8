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
use Drupal\block\Entity\Block;
use Drupal\rcb_theme\RCBNodeImage;

/**
 * Implements template_preprocess_page().
 */
function rcb_theme_preprocess_page(&$variables) {
  $variables['header_attributes']['class'] = ['uk-hidden@m'];
  $variables['page_attributes']['class'] = [
    'uk-container',
    'uk-container-expand',
    'uk-position-relative',
  ];
  $variables['content_attributes']['class'] = ['uk-width-expand'];
  $variables['sidebar_first_attributes']['class'] = [
    'uk-visible@m',
    'uk-width-medium',
  ];
  $variables['sidebar_second_attributes']['class'] = [
    'uk-visible@l',
    'uk-width-medium',
  ];
  $variables['footer_attributes'] = new Attribute;
  $variables['footer_attributes']->setAttribute('id', 'page--footer');
  $variables['footer_attributes']->addClass('uk-container');
  $variables['footer_attributes']->addClass('uk-container-expand');
  $variables['footer_attributes']->setAttribute('role', 'contentinfo');

  $node = isset($variables['node']) ? $variables['node'] : FALSE;
  $fid = $node && isset($node->field_image->entity) ? $node->field_image->entity->id() : NULL;
  $variables['node_image'] = RCBNodeImage::buildResponsiveImage($fid, 'wide');
  if (!empty($variables['node_image'])) {
    $request = \Drupal::request();
    $route_match = \Drupal::routeMatch();
    $variables['page_title'] = \Drupal::service('title_resolver')->getTitle($request, $route_match->getRouteObject());
    $variables['content_attributes']['class'][] = 'page-title-hidden';
  }
}

/**
 * Implements template_preprocess_block().
 */
function rcb_theme_preprocess_block(&$variables) {
  $base_plugin_id = $variables['base_plugin_id'];
  $book_navigation = $base_plugin_id == 'book_navigation';
  $block = Block::load($variables['elements']['#id']);
  $region = $block->getRegion();

  if ($book_navigation) {
    switch ($region) {
      case 'offcanvas':
        foreach ($variables['content'] as $key => $content) {
          if (is_array($content) && isset($content['#theme'])) {
            $variables['content'][$key]['#theme'] = 'book_tree__offcanvas';
          }
        }
        break;

      case 'sidebar_first':
      case 'sidebar_second':
        foreach ($variables['content'] as $key => $content) {
          if (is_array($content) && isset($content['#theme'])) {
            $variables['content'][$key]['#theme'] = 'book_tree__sidebar';
          }
        }
        break;
    }
  }
}

/**
 * Implements template_preprocess_container().
 */
function rcb_theme_preprocess_container(&$variables) {
  $type = $variables['element']['#type'];

  switch ($type) {
    case 'actions':
      $variables['attributes']['class'][] = 'uk-margin';
  }
}

/**
 * Implements template_preprocess_form().
 */
function rcb_theme_preprocess_form(&$variables) {
  $form_id = $variables['element']['#form_id'];

  switch ($form_id) {
    case 'search_form':
      $variables['layout'] = 'horizontal';
      break;

    default:
      $variables['layout'] = 'stacked';
  }
}

/**
 * Implements template_preprocess_form_element().
 */
function rcb_theme_preprocess_form_element(&$variables) {
  $element = $variables['element'];
  $type = $element['#type'];

  $form_advanced = $type == 'checkbox' || $type == 'radio';
  if ($form_advanced) {
    $variables['label_text'] = $variables['label']['#title'];
  }
}

/**
 * Implements template_preprocess_input().
 */
function rcb_theme_preprocess_input(&$variables) {
  $type = $variables['element']['#type'];

  if ($type == 'submit') {
    $variables['button_icon'] = FALSE;

    if (isset($variables['element']['#icon'])) {
      $icon = $variables['element']['#icon'];
      $variables['attributes']['class'][] = 'uk-button-text';
      $variables['attributes']['uk-icon'] = "icon: $icon";
      $variables['button_icon'] = TRUE;
    }
    else {
      $value = $variables['element']['#value']->__toString();
      switch ($value) {
        case 'Advanced search':
        case 'Log in':
        case 'Preview':
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
}

/**
 * Implements template_preprocess_menu().
 */
function rcb_theme_preprocess_menu(&$variables) {
  $menu_name = $variables['menu_name'];
  $variables['attributes']['class'][] = 'menu';
  $variables['attributes']['class'][] = 'menu--' . str_replace('_', '-', $menu_name);

  switch ($menu_name) {
    case 'footer':
      $variables['attributes']['class'][] = 'uk-subnav';
  }
}

/**
 * Implements template_preprocess_user().
 */
function rcb_theme_preprocess_user(&$variables) {
  if ($variables['content']['member_for']) {
    $created = $variables['elements']['#user']->getCreatedTime();
    $member_for = \Drupal::service('date.formatter')
      ->formatInterval(\Drupal::time()->getRequestTime() - $created);
    $variables['content']['member_for']['#markup'] = t('<p><strong>Member for</strong> @member_for</p>', ['@member_for' => $member_for]);
  }
}
