#pragma once

/* FONT */
#define FONT_PATH "../resources/ui/ARCADEPI.TTF"

/* CSV FILER */
#define CSV_PATH_TERRAIN      "../levels/%d/level_%d_terrain.csv"
#define CSV_PATH_GRASS        "../levels/%d/level_%d_grass.csv"
#define CSV_PATH_PLAYER_SPAWN "../levels/%d/level_%d_player.csv"
#define CSV_PATH_COINS        "../levels/%d/level_%d_coins.csv"
#define CSV_PATH_BG_PALMS     "../levels/%d/level_%d_bg_palms.csv"
#define CSV_PATH_FG_PALMS     "../levels/%d/level_%d_fg_palms.csv"
#define CSV_PATH_CRATE        "../levels/%d/level_%d_crates.csv"
#define CSV_PATH_ENEMIES      "../levels/%d/level_%d_enemies.csv"
#define CSV_PATH_CONSTRAINTS  "../levels/%d/level_%d_constraints.csv"

/* SPRITESHEET FILER */
#define SPRITESHEET_TERRAIN "../resources/terrain/terrain_tiles.png"
#define SPRITESHEET_GRASS "../resources/decoration/grass/grass.png"
#define SPRITESHEET_COINS "../resources/coins/coin_tiles.png"
#define SPRITESHEET_CONSTRAINTS "../resources/enemy/setup_tile.png"

/* SPRITES */
#define SPRITE_PLAYER "../resources/character/idle/1.png"
#define SPRITE_CRATE "../resources/terrain/crate.png"
#define SPRITE_SKY_TOP "../resources/decoration/sky/sky_top.png"
#define SPRITE_SKY_MIDDLE "../resources/decoration/sky/sky_middle.png"
#define SPRITE_SKY_BOTTOM "../resources/decoration/sky/sky_bottom.png"

/* -- ANIMATION PATHS -- */
/* PLAYER */
#define ANIMATION_PLAYER_RUN "../resources/character/run"
#define ANIMATION_PLAYER_IDLE "../resources/character/idle"
#define ANIMATION_PLAYER_FALL "../resources/character/fall"
#define ANIMATION_PLAYER_JUMP "../resources/character/jump"

/* ENEMY*/
#define ANIMATION_ENEMY_EXPLOSION "../resources/enemy/explosion"
#define ANIMATION_ENEMY_RUN "../resources/enemy/run"

/* WATER */
#define ANIMATION_WATER "../resources/decoration/water"

/* COIN */
#define ANIMATION_COIN_SILVER "../resources/coins/silver"
#define ANIMATION_COIN_GOLD "../resources/coins/gold"

/* FG & BG PALMS */
#define ANIMATION_PALM_BG "../resources/terrain/palm_bg"
#define ANIMATION_PALM_LARGE "../resources/terrain/palm_large"
#define ANIMATION_PALM_SMALL "../resources/terrain/palm_small"

/* PARTICLES */
#define ANIMATION_PARTICLE_JUMP "../resources/character/dust_particles/jump"
#define ANIMATION_PARTICLE_LAND "../resources/character/dust_particles/land"
#define ANIMATION_PARTICLE_RUN  "../resources/character/dust_particles/run"

/* SOUNDS & MUSIC */
#define MUSIC_LEVEL_PATH "../audio/level_music.wav"
#define MUSIC_OVERWORLD_PATH "../audio/overworld_music.wav"
#define SOUND_COIN_PATH "../audio/effects/coin.wav"
#define SOUND_HIT_PATH "../audio/effects/hit.wav"
#define SOUND_JUMP_PATH "../audio/effects/jump.wav"
#define SOUND_STOMP_PATH "../audio/effects/stomp.wav"

/* UI */
#define UI_HEALTH_BAR_PATH "../resources/ui/health_bar.png"
#define UI_COIN_PATH "../resources/ui/coin.png"
