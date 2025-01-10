/**
 * @file dark_slider.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "dark_slider_private_gen.h"
#include "ui.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void dark_slider_set_color(lv_obj_t * obj, lv_color_t c)
{
    lv_obj_set_style_bg_color(obj, c, LV_PART_INDICATOR);
    lv_obj_set_style_bg_color(obj, lv_color_darken(c, 80), LV_PART_INDICATOR | LV_STATE_PRESSED);
}

void dark_slider_constructor_hook(lv_obj_t * obj)
{

}

void dark_slider_destructor_hook(lv_obj_t * obj)
{

}

void dark_slider_event_hook(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);

    if(code == LV_EVENT_REFR_EXT_DRAW_SIZE) {
        int32_t * s = lv_event_get_param(e);
        *s = LV_MAX(*s, 60);
    }
    else if(code == LV_EVENT_DRAW_TASK_ADDED) {
        lv_draw_task_t * draw_task = lv_event_get_param(e);
        if(draw_task == NULL || lv_draw_task_get_type(draw_task) != LV_DRAW_TASK_TYPE_FILL) return;
        lv_draw_rect_dsc_t * draw_rect_dsc = lv_draw_task_get_draw_dsc(draw_task);

        if(draw_rect_dsc->base.part == LV_PART_KNOB && lv_obj_has_state(obj, LV_STATE_PRESSED)) {
            char buf[8];
            lv_snprintf(buf, sizeof(buf), "%"LV_PRId32, lv_slider_get_value(obj));

            lv_point_t text_size;
            lv_text_get_size(&text_size, buf, LV_FONT_DEFAULT, 0, 0, LV_COORD_MAX, LV_TEXT_FLAG_NONE);

            lv_area_t txt_area;
            lv_area_t draw_task_area;
            lv_draw_task_get_area(draw_task, &draw_task_area);
            txt_area.x1 = draw_task_area.x1 + lv_area_get_width(&draw_task_area) / 2 - text_size.x / 2;
            txt_area.x2 = txt_area.x1 + text_size.x;
            txt_area.y2 = draw_task_area.y1 - 10;
            txt_area.y1 = txt_area.y2 - text_size.y;

            lv_area_t bg_area;
            bg_area.x1 = txt_area.x1 - LV_DPX(8);
            bg_area.x2 = txt_area.x2 + LV_DPX(8);
            bg_area.y1 = txt_area.y1 - LV_DPX(8);
            bg_area.y2 = txt_area.y2 + LV_DPX(8);

            lv_draw_rect_dsc_t rect_dsc;
            lv_draw_rect_dsc_init(&rect_dsc);
            rect_dsc.bg_color = lv_palette_darken(LV_PALETTE_RED, 3);
            rect_dsc.radius = LV_DPX(5);
            lv_draw_rect(draw_rect_dsc->base.layer, &rect_dsc, &bg_area);

            lv_draw_label_dsc_t label_dsc;
            lv_draw_label_dsc_init(&label_dsc);
            label_dsc.color = lv_color_white();
            label_dsc.text = buf;
            label_dsc.text_local = 1;
            lv_draw_label(draw_rect_dsc->base.layer, &label_dsc, &txt_area);
        }
    }
}



/**********************
 *   STATIC FUNCTIONS
 **********************/