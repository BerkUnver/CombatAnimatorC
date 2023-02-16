#ifndef EDITOR_HISTORY
#define EDITOR_HISTORY

#include <stdlib.h>
#include "cjson/cJSON.h"
#include "combat_shape.h"

#define HISTORY_BUFFER_SIZE_INCREMENT 1024
#define FRAME_DURATION_UNIT_PER_SECOND 1000.0f
#define FRAME_INFO_DEFAULT (FrameInfo) {.duration = 100, .canCancel = false}
#define STR_SHAPES "shapes"
#define STR_FRAMES "frames"
#define STR_FRAME_DURATIONS "frameDurations"
#define STR_FRAME_INFO_DURATION "duration"
#define STR_FRAME_INFO_CAN_CANCEL "canCancel"
#define STR_SHAPE_ACTIVE_FRAMES "shapeActiveFrames"

#define STR_MAGIC "magic"
#define STR_MAGIC_VALUE "CombatAnimator"
#define STR_VERSION "version"
#define VERSION_NUMBER 1

typedef struct FrameInfo {
    int duration;
    bool canCancel;
} FrameInfo;

typedef struct EditorState {
    CombatShape *shapes;
    int shapeCount;
    bool *_shapeActiveFrames;
    FrameInfo *frames;
    int frameCount;
    int shapeIdx;
    int frameIdx;
} EditorState;

typedef struct EditorHistory {
    EditorState *_states;
    int _currentStateIdx;
    int _mostRecentStateIdx;
    int _statesLength;
} EditorHistory;

typedef enum ChangeOptions {
    UNDO,
    REDO
} ChangeOptions;

EditorState AllocEditorState(int frameCount);
void FreeEditorState(EditorState *state);
bool GetShapeActive(EditorState *state, int frameIdx, int shapeIdx);
void SetShapeActive(EditorState *state, int frameIdx, int shapeIdx, bool enabled);

void AddShape(EditorState *state, CombatShape shape);
bool RemoveShape(EditorState *state, int idx);
void AddFrame(EditorState *state);
EditorState EditorStateDeepCopy(EditorState *state);
cJSON *SerializeState(EditorState state);

bool DeserializeState(cJSON *json, EditorState *state);

EditorHistory AllocEditorHistory(EditorState *initial);
void FreeEditorHistory(EditorHistory *history);

void CommitState(EditorHistory *history, EditorState *state);
void ChangeState(EditorHistory *history, EditorState *state, ChangeOptions option);

#endif
