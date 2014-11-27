(function ($) {
  $(document).ready(function() {
    $('.date-tp').datetimepicker({
      language: 'ru',
    });
	
    $(".date-tp").on("dp.show", function (e) {

      $(this).addClass('dontClose');
      $('.bootstrap-datetimepicker-widget').each(function() {
        if ($(this).hasClass('opened')) {
          $(this).removeClass('opened');
          $(this).removeClass('picker-open');
          $(this).hide();
        }
        if ($(this).hasClass('picker-open')) {
          $(this).addClass('opened');
        } 
      });
      
    });
    $(".date-tp").on("dp.hide", function (e) {
      
    });

  });

})(window.jQuery);
