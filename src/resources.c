#include "resources.h"
#include "files.h"
#include <raylib.h>
#include <stdlib.h>
#include <string.h>

// Kan kun benyttes gennem funktioner fra resources.h
static ResourceCollection rs_collection;
static SpritesheetCollection spsheet_collection;
static AnimationCollection anim_collection;

/*
 * Finder resource ved at loope igennem og tjekke manuelt alle ids
 * - ikke den bedste løsning, men når vi "kun" har 150 resources er det okay
 */
Resource *getResource(const char *id) {
  if (id == NULL) {
    TraceLog(LOG_ERROR, "[RESOURCES] getResource blev kaldt med NULL id");
    return NULL;
  }

  for (int i = 0; i < rs_collection.size; ++i) {
    if (strcmp(rs_collection.resources[i].id, id) == 0) {
      return &rs_collection.resources[i];
    }
  }

  TraceLog(LOG_WARNING, "[RESOURCES] Kunne ikke finde resource med id \"%s\"",
           id);
  return NULL;
}

/*
 * Load en resource ind i rs_collection.
 * */
Resource *loadResource(const char *id, Texture2D texture) {
  // Tjek om id allerede eksisterer og genbrug pladsen
  for (int i = 0; i < rs_collection.size; ++i) {
    if (strcmp(rs_collection.resources[i].id, id) == 0) {
      if (rs_collection.resources[i].is_loaded) {
        UnloadTexture(rs_collection.resources[i].texture);
      }

      rs_collection.resources[i].texture = texture;
      rs_collection.resources[i].is_loaded = true;

      // TraceLog(LOG_INFO, "[RESOURCES] Registreret resource med id \"%s\"
      // successfuldt", id);
      return &rs_collection.resources[i];
    }
  }

  // Tjek om der er nogen resources der er unloaded som vi kan genbruge plads
  // hos
  for (int i = 0; i < rs_collection.size; ++i) {
    if (!rs_collection.resources[i].is_loaded) {
      rs_collection.resources[i].id = strdup(id);
      rs_collection.resources[i].texture = texture;
      rs_collection.resources[i].is_loaded = true;
      // TraceLog(LOG_INFO, "[RESOURCES] Registreret resource med id \"%s\"
      // successfuldt", id);
      return &rs_collection.resources[i];
    }
  }

  // Tjek om vi har for mange resources
  if (rs_collection.size < MAX_RESOURCES) {
    rs_collection.resources[rs_collection.size++] = (Resource){
        .id = strdup(id),
        .texture = texture,
        .is_loaded = true,
    };

    // TraceLog(LOG_INFO, "[RESOURCES] Registreret resource med id \"%s\"
    // successfuldt", id);
    return &rs_collection.resources[rs_collection.size - 1];
  }

  TraceLog(
      LOG_ERROR,
      "[RESOURCES] Kunne ikke indlæse resource id \"%s\", ingen plads tilbage",
      id);

  return NULL;
}

/* int size er antallet af tiles / sprites fra et billede. Eksempel: 16 = 4x4 */
Spritesheet *loadSpritesheet(const char *id, const char *file_path, int width,
                             int height) {
  if (id == NULL || file_path == NULL) {
    TraceLog(LOG_ERROR, "[RESOURCES] Parametrene 'id' og 'file_path' i "
                        "funktionen \"loadSpritesheet\" må ikke være NULL");
    return NULL;
  }

  if (!FileExists(file_path)) {
    TraceLog(LOG_ERROR, "[RESOURCES] Filen \"%s\" findes ikke", file_path);
    return NULL;
  }

  Spritesheet spsheet = {.id = strdup(id), .size = 0};

  Image spsheet_image = LoadImage(file_path);
  for (int i = 0; i < (height / TILE_SIZE); ++i) {
    for (int j = 0; j < (width / TILE_SIZE); ++j) {

      Rectangle img_rect = (Rectangle){
          .height = TILE_SIZE,
          .width = TILE_SIZE,
          .x = j * TILE_SIZE,
          .y = i * TILE_SIZE,
      };

      Image sprite_img = ImageFromImage(spsheet_image, img_rect);

      char dest[128];
      snprintf(dest, sizeof(dest), "%s_%d", id, spsheet.size);

      Resource *res = loadResource(dest, LoadTextureFromImage(sprite_img));
      if (res != NULL && spsheet.size < MAX_SPRITESHEET_RESOURCES) {
        spsheet.resources[spsheet.size++] = res;
      } else {
        TraceLog(LOG_ERROR,
                 "[RESOURCES] Kunne ikke indlæse texture fra billede");
        return NULL;
      }

      UnloadImage(sprite_img);
    }
  }

  UnloadImage(spsheet_image);

  spsheet_collection.spritesheets[spsheet_collection.size++] = spsheet;

  return &spsheet_collection.spritesheets[spsheet_collection.size - 1];
}

Spritesheet *getSpritesheet(const char *id) {
  if (id == NULL) {
    TraceLog(LOG_ERROR, "[RESOURCES] getSpritesheet blev kaldt med NULL id");
    return NULL;
  }

  for (int i = 0; i < spsheet_collection.size; ++i) {
    if (strcmp(spsheet_collection.spritesheets[i].id, id) == 0) {
      return &spsheet_collection.spritesheets[i];
    }
  }

  TraceLog(LOG_WARNING,
           "[RESOURCES] Kunne ikke finde spritesheet med id \"%s\"", id);
  return NULL;
}

Animation *loadAnimation(const char *id, const char *dir_path) {
  if(id == NULL || dir_path == NULL) {
    TraceLog(LOG_ERROR, "[RESOURCES] Mangler id og/eller dir_path til loadAnimation()");
    return NULL;
  }

  FilePathList fp_list = LoadDirectoryFiles(dir_path);
  if (fp_list.count <= 0) {
    TraceLog(LOG_ERROR,
             "[RESOURCES] Kunne ikke indlæse animationer for id: \"%s\" "
             "dir_path: %s",
             id, dir_path);
    return NULL;
  }

  Resource *rs_arr[MAX_ANIMATION_LENGTH];
  size_t count = 0;
  char id_buffer[128];
  
  /* Sorter alle filer i numerisk rækkefølge */
  qsort(fp_list.paths, fp_list.count, sizeof(char *), compareFilePaths);
  for (size_t i = 0; i < fp_list.count; ++i) {
    if(count >= MAX_ANIMATION_LENGTH) {
      TraceLog(LOG_WARNING, "[RESOURCES] Opnået maks antal frames for animation \"%s\"", id);
      break;
    }

    snprintf(id_buffer, sizeof(id_buffer), "%s_%zu", id, i);

    rs_arr[count++] = loadResource(id_buffer, LoadTexture(fp_list.paths[i]));
  }

  Animation anim = {
    .id = strdup(id),
    .count = count,
  };
  memcpy(anim.resources, rs_arr, count * sizeof(Resource *));

  anim_collection.animations[anim_collection.count++] = anim;

  return &anim_collection.animations[anim_collection.count - 1];
}

Animation *getAnimation(const char *id) { 
  if(id == NULL) {
    TraceLog(LOG_ERROR, "[RESOURCES] id må ikke være NULL (getAnimation)");
    return NULL;
  }

  for(size_t i = 0; i < anim_collection.count; ++i) {
    if(strcmp(anim_collection.animations[i].id, id) == 0) {
      return &anim_collection.animations[i];
    }
  }

  return NULL;
}

void unloadSpritesheet(Spritesheet *spsheet) {
  for (int i = 0; i < spsheet->size; ++i) {
    unloadResource(spsheet->resources[i]);
  }

  free(spsheet->id);
  spsheet->size = 0;
}

void unloadResourceByID(const char *id) {
  Resource *rs = getResource(id);
  if (rs == NULL) {
    TraceLog(LOG_WARNING, "[RESOURCES] Forsøgte at unloade resource med id "
                          "\"%s\" men fik et ugyldigt id");
    return;
  }

  if (rs->is_loaded) {
    UnloadTexture(rs->texture);
    rs->is_loaded = false;
    free(rs->id);
  }
}

void unloadResource(Resource *resource) {
  if (resource->is_loaded) {
    UnloadTexture(resource->texture);
    resource->is_loaded = false;
    free(resource->id);
  }
}

void unloadAllResources() {
  for (int i = 0; i < rs_collection.size; ++i) {
    unloadResource(&rs_collection.resources[i]);
  }

  rs_collection.size = 0;
  TraceLog(LOG_INFO, "[RESOURCES] Alle resources er blevet unloadet");
}

void unloadAllSpritesheets() {
  for (int i = 0; i < spsheet_collection.size; ++i) {
    unloadSpritesheet(&spsheet_collection.spritesheets[i]);
  }

  spsheet_collection.size = 0;
}
