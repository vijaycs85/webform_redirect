(function ($) {

    Drupal.behaviors.webform_redirect = function(context, settings) {
        function ruleRepeater(container, fieldsetSelecter, addButtonLabel) {
            var addButton = $('<div class="clear"></div><input type="button" class="add-more" /></div>').val(addButtonLabel).click(function() {
                var hiddenFieldsets = fieldsets.not(':visible');
                hiddenFieldsets.filter(':first').fadeIn();
                if(hiddenFieldsets.size() < 2) {
                    addButton.hide();
                }
            });

            var fieldsets = container.find(fieldsetSelecter);

            fieldsets.filter(':last').after($('<div/>').append(addButton))
        }

        var $rows = $('.rule-wrapper');
        $rows.each(function(i) {
            var $field = $('.form-select', this);
            if ($field.val() == '' && i > 0) {
                $(this).hide();
            }
          });

        ruleRepeater($('#webform-configure-form'), '.rule-wrapper', 'Add an item');
    };

})(jQuery);