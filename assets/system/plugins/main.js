/**  Функция для закрытия меню sidr **/
function watchForSidr(selector) {
  if (typeof(selector) != 'undefined') {
    selector.trigger('click');
  }
}

(function ($) {

  // iOS orientation
  $(document).ready(function() {
    if (navigator.userAgent.match(/iPhone/i) || navigator.userAgent.match(/iPad/i)) {
      var viewportmeta = document.querySelector('meta[name="viewport"]');
      if (viewportmeta) {
        viewportmeta.content = 'width=device-width, minimum-scale=1.0, maximum-scale=1.0, initial-scale=1.0';
        document.body.addEventListener('gesturestart', function () {
          viewportmeta.content = 'width=device-width, minimum-scale=0.25, maximum-scale=1.6';
        }, false);
      }
    }
    
 
    
    // Closing dropdown menus when search activated
    $('.sb-search').on('click', function() {
      $('.dropdown.open').removeClass('open');
    });    
    
    //Closing menu sidr on resizing window
    $(window).resize(function () {
      watchForSidr($('.sidr-open .menu-open-link'));
    });
    
  }); 

})(window.jQuery);


