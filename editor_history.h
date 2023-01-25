#ifndef EDITOR_HISTORY
#define EDITOR_HISTORY

#include <stdlib.h>
#include "hitbox.h"

#define HISTORY_BUFFER_SIZE_INCREMENT 1024

typedef struct EditorState {
    Hitbox *hitboxes;
    int hitboxCount;
    bool *_hitboxActiveFrames;
    int frameCount;
    int hitboxIdx;
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

EditorState AllocEditorState(int frames);
void FreeEditorState(EditorState state);

bool GetHitboxActive(EditorState *state, int frameIdx, int hitboxIdx);
void SetHitboxActive(EditorState *state, int frameIdx, int hitboxIdx, bool enabled);
void AddHitbox(EditorState *state, Hitbox hitbox);
EditorState EditorStateDeepCopy(EditorState state);

EditorHistory AllocEditorHistory(EditorState *initial);
void FreeEditorHistory(EditorHistory history);

void CommitState(EditorHistory *history, EditorState *state);
void ChangeState(EditorHistory *history, EditorState *state, ChangeOptions option);

#endif