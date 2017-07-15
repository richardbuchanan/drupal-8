/**
 * @file
 * Attaches behaviors for rcb.
 */

(function ($) {

  'use strict';

  Drupal.behaviors.rcb = {
    attach: function () {
      var mediaAll = $('[media="bogusAll"]');
      mediaAll.prop('media', 'all');
      var loginLink = $('[href="/user/login"]');
      var loginModal = $("#login-modal");
      var loginContent = loginModal.clone();

      loginModal.remove();

      loginLink
        .prop('href', '#login-modal')
        .attr('uk-toggle', '')
        .after(loginContent)
        .click(function () {
          UIkit.modal('#login-modal').toggle();
      });

      $('pre code').each(function(i, block) {
        hljs.highlightBlock(block);
      });
    }
  };
})(jQuery);
