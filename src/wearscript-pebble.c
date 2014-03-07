#include <pebble.h>

static const uint32_t CMD_KEY = 0x00;
static const uint32_t CMD_SELECT = 0x00;
static const uint32_t CMD_UP = 0x01;
static const uint32_t CMD_DOWN = 0x02;
static const uint32_t CMD_MULTI_SELECT = 0x03;

static Window *window;
static TextLayer *text_layer;
static TextLayer *text_layer_x;
static TextLayer *text_layer_y;
static TextLayer *text_layer_z;

char bufx[1024];
char bufy[1024];
char bufz[1024];

static void send_message(uint32_t CMD) {
  DictionaryIterator *iter;
  app_message_outbox_begin(&iter);
  dict_write_uint8(iter, CMD_KEY, CMD);
  app_message_outbox_send();
}

// Click Handlers
static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(text_layer, "Select");
  send_message(CMD_SELECT);
}

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(text_layer, "Up");
  send_message(CMD_UP);
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(text_layer, "Down");
  send_message(CMD_DOWN);
}

static void select_multi_click_handler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(text_layer, "Multi");
  send_message(CMD_MULTI_SELECT);
}

// Configure click handlers
static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
  window_multi_click_subscribe(BUTTON_ID_SELECT, 2, 10, 100, true, select_multi_click_handler);
}

// Message handlers
void out_sent_handler(DictionaryIterator *sent, void *context) {
  // outgoing message was delivered
  text_layer_set_text(text_layer, "Pass");
}


void out_failed_handler(DictionaryIterator *failed, AppMessageResult reason, void *context) {
  // outgoing message failed
  text_layer_set_text(text_layer, "Fail");
}


void in_received_handler(DictionaryIterator *received, void *context) {
  // incoming message received
}


void in_dropped_handler(AppMessageResult reason, void *context) {
  // incoming message dropped
}

// Accelerometer handlers
static void accel_tap_handler(AccelAxisType axis, int32_t direction) {
  // Send data to phone
}


static void accel_data_handler(AccelData *data, uint32_t num_samples) {
  snprintf(bufx, 100,  "%d", data[0].x);
  snprintf(bufy, 100,  "%d", data[0].y);
  snprintf(bufz, 100,  "%d", data[0].z);
  
  text_layer_set_text(text_layer_x, bufx);
  text_layer_set_text(text_layer_y, bufy);
  text_layer_set_text(text_layer_z, bufz);
}

static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  text_layer = text_layer_create((GRect) { .origin = { 0, 0 }, .size = { bounds.size.w, 20 } });
  text_layer_set_text(text_layer, "Press a button");
  text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(text_layer));

  // XYZ for accelerometer
  text_layer_x = text_layer_create((GRect) { .origin = { 0, 27}, .size = { bounds.size.w, 20 } });
  text_layer_set_text(text_layer_x, "this is x");
  text_layer_set_text_alignment(text_layer_x, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(text_layer_x));

  text_layer_y = text_layer_create((GRect) { .origin = { 0, 54 }, .size = { bounds.size.w, 20} });
  text_layer_set_text(text_layer_y, "this is y");
  text_layer_set_text_alignment(text_layer_y, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(text_layer_y));
  

  text_layer_z = text_layer_create((GRect) { .origin = { 0,  81}, .size = { bounds.size.w, 20} });
  text_layer_set_text(text_layer_z, "this is y");
  text_layer_set_text_alignment(text_layer_z, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(text_layer_z));
  
}

static void window_unload(Window *window) {
  text_layer_destroy(text_layer);
}

static void init(void) {
  // Communication with android app
  app_message_register_inbox_received(in_received_handler);
  app_message_register_inbox_dropped(in_dropped_handler);
  app_message_register_outbox_sent(out_sent_handler);
  app_message_register_outbox_failed(out_failed_handler);
  const uint32_t inbound_size = 64;
  const uint32_t outbound_size = 64;
  app_message_open(inbound_size, outbound_size);

  // Accelerometer subscriber
  accel_tap_service_subscribe(&accel_tap_handler);
  accel_data_service_subscribe(10, &accel_data_handler);

  window = window_create();
  window_set_click_config_provider(window, click_config_provider);
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });
  const bool animated = true;
  window_stack_push(window, animated);
}

static void deinit(void) {
  window_destroy(window);
  accel_tap_service_unsubscribe();
  accel_data_service_unsubscribe();
}

int main(void) {
  init();

  APP_LOG(APP_LOG_LEVEL_DEBUG, "Done initializing, pushed window: %p", window);

  app_event_loop();
  deinit();
}
