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

      var $html = $('html');
      var $body = $('body');
      var $documentHeight = $(document).height();

      if ($body.hasClass('toolbar-vertical')) {
        $html.addClass('toolbar-vertical');

        if ($body.height() < $documentHeight) {
          $body.height($documentHeight - 40)
        }
      }
      else {
        if ($body.hasClass('toolbar-horizontal')) {
          $html.addClass('toolbar-horizontal');

          if ($body.height() < $documentHeight) {
            if ($body.hasClass('toolbar-tray-open')) {
              $body.height($documentHeight - 79)
            }
            else {
              $body.height($documentHeight - 40)
            }
          }
        }
      }
      if ($body.hasClass('toolbar-tray-open')) {
        $html.addClass('toolbar-tray-open');
      }

      if (Drupal.toolbar) {
        var model = Drupal.toolbar.models.toolbarModel;

        if (model) {
          model.on('change:orientation', function (model, orientation) {
            $html
              .toggleClass('toolbar-vertical', (orientation === 'vertical'))
              .toggleClass('toolbar-horizontal', (orientation === 'horizontal'));

            if (orientation === 'vertical') {
              if ($body.height() < $documentHeight) {
                $body.height($documentHeight - 40)
              }
            }
            if (orientation === 'horizontal') {
              if ($body.height() < $documentHeight) {
                if ($body.hasClass('toolbar-tray-open')) {
                  $body.height($documentHeight - 79)
                }
                else {
                  $body.height($documentHeight - 40)
                }
              }
            }
          });

          model.on('change:activeTray', function (model, tray) {
            $html.toggleClass('toolbar-tray-open', !!tray);
            if (tray && $body.hasClass('toolbar-horizontal')) {
              $body.height($documentHeight - 79)
            }
            else {
              $body.height($documentHeight - 40)
            }
          })
        }
      }
    }
  }
})(jQuery, Drupal);
