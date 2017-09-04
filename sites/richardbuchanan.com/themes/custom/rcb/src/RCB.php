<?php
namespace Drupal\rcb;
use Drupal\Core\Link;
use Drupal\Core\Url;
/**
 * Provides helper functions for the RCB theme.
 */
class RCB {
  public static function systemPoweredByContent() {
    // Create the urls.
    $drupal_url = Url::fromUri('https://www.drupal.org');
    $uikit_url = Url::fromUri('https://getuikit.com');
    $url_options = array('attributes' => array('target' => '_blank'));
    $drupal_url->setOptions($url_options);
    $uikit_url->setOptions($url_options);
    // Set link text.
    $drupal_text = t('Drupal');
    $uikit_text = t('UIkit');
    // Create the links.
    $drupal_link = Link::fromTextAndUrl($drupal_text, $drupal_url);
    $uikit_link = Link::fromTextAndUrl($uikit_text, $uikit_url);
    // Creat the markup.
    $content = [
      '#markup' => '<span>' . t('Powered by ') . $drupal_link->toString() . ' and ' . $uikit_link->toString() . '</span>',
    ];
    return $content;
  }

}
