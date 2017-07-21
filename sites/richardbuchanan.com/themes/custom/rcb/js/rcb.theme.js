/**
 * @file
 * Attaches behaviors for rcb.
 */

(function ($, Drupal) {

  'use strict';

  Drupal.behaviors.rcb = {
    attach: function () {
      $('pre code').each(function(i, block) {
        hljs.highlightBlock(block);
      });
    }
  }
})(jQuery, Drupal);
