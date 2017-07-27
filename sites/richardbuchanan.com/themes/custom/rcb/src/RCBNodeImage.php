<?php

namespace Drupal\rcb;

use Drupal\file\Entity\File;
use Drupal\system_test\Controller\PageCacheAcceptHeaderController;

/**
 * Provides helper functions for node images.
 */
class RCBNodeImage {

  /**
   * Builds a responsive image.
   *
   * @param integer $fid
   *   The file id to build.
   * @param string $responsive_image_style
   *   The machine-name of the responsive image style. Defaults to narrow.
   *
   * @return array
   *   Returns a renderable array of the image if fid is valid, otherwise an
   *   empty array.
   */
  public static function buildResponsiveImage($fid = 0, $responsive_image_style = 'narrow') {
    if ($fid) {
      $file = File::load($fid);

      if ($file) {
        $variables = [
          'responsive_image_style_id' => $responsive_image_style,
          'uri' => $file->getFileUri(),
        ];

        // The image.factory service will check if our image is valid.
        $image = \Drupal::service('image.factory')->get($file->getFileUri());

        if ($image->isValid()) {
          $variables['width'] = $image->getWidth();
          $variables['height'] = $image->getHeight();
        }
        else {
          $variables['width'] = $variables['height'] = NULL;
        }

        $image_build = [
          '#theme' => 'responsive_image',
          '#width' => $variables['width'],
          '#height' => $variables['height'],
          '#responsive_image_style_id' => $variables['responsive_image_style_id'],
          '#uri' => $variables['uri'],
        ];

        // Add the file entity to the cache dependencies.
        // This will clear our cache when this entity updates.
        $renderer = \Drupal::service('renderer');
        $renderer->addCacheableDependency($image_build, $file);

        // Return the render array as block content.
        return [
          'image' => $image_build,
        ];
      }
      else {
        // Image not found, return empty block.
        return [];
      }
    }
    else {
      // Invalid fid, return empty block.
      return [];
    }
  }
}