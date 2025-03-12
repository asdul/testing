// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.5.0
// LVGL version: 9.1.0
// Project name: SquareLine_Project

#include "ui.h"

void ui_Screen1_screen_init(void)
{
    ui_Screen1 = lv_obj_create(NULL);
    lv_obj_remove_flag(ui_Screen1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Switch1 = lv_switch_create(ui_Screen1);
    lv_obj_set_width(ui_Switch1, 119);
    lv_obj_set_height(ui_Switch1, 57);
    lv_obj_set_x(ui_Switch1, -7);
    lv_obj_set_y(ui_Switch1, -28);
    lv_obj_set_align(ui_Switch1, LV_ALIGN_CENTER);
    lv_obj_add_state(ui_Switch1, LV_STATE_CHECKED);       /// States


    ui_Panel1 = lv_obj_create(ui_Screen1);
    lv_obj_set_width(ui_Panel1, 100);
    lv_obj_set_height(ui_Panel1, 50);
    lv_obj_set_x(ui_Panel1, -3);
    lv_obj_set_y(ui_Panel1, 75);
    lv_obj_set_align(ui_Panel1, LV_ALIGN_CENTER);
    lv_obj_remove_flag(ui_Panel1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Label1 = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_Label1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label1, -7);
    lv_obj_set_y(ui_Label1, 75);
    lv_obj_set_align(ui_Label1, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label1, "on");

    lv_obj_add_event_cb(ui_Switch1, ui_event_Switch1, LV_EVENT_ALL, NULL);

}
