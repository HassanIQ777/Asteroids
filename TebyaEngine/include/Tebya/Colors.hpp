#pragma once

#include <SDL2/SDL.h>
#include <algorithm>
#include <cstdint>

namespace tebya::Colors {

// ============================================================================
// BASIC & TIMELESS
// ============================================================================
constexpr SDL_Color Black = {0, 0, 0, 255};
constexpr SDL_Color White = {255, 255, 255, 255};
constexpr SDL_Color Gray = {128, 128, 128, 255};
constexpr SDL_Color DarkGray = {64, 64, 64, 255};
constexpr SDL_Color LightGray = {192, 192, 192, 255};
constexpr SDL_Color Transparent = {0, 0, 0, 0};

// ============================================================================
// REDS (From Crimson to Rose)
// ============================================================================

constexpr SDL_Color Red = {255, 0, 0, 255};
constexpr SDL_Color DarkRed = {139, 0, 0, 255};
constexpr SDL_Color Crimson = {220, 20, 60, 255};
constexpr SDL_Color Firebrick = {178, 34, 34, 255};
constexpr SDL_Color IndianRed = {205, 92, 92, 255};
constexpr SDL_Color LightCoral = {240, 128, 128, 255};
constexpr SDL_Color Salmon = {250, 128, 114, 255};
constexpr SDL_Color DarkSalmon = {233, 150, 122, 255};
constexpr SDL_Color LightSalmon = {255, 160, 122, 255};
constexpr SDL_Color Tomato = {255, 99, 71, 255};
constexpr SDL_Color OrangeRed = {255, 69, 0, 255};
constexpr SDL_Color HotPink = {255, 105, 180, 255};
constexpr SDL_Color DeepPink = {255, 20, 147, 255};
constexpr SDL_Color MediumVioletRed = {199, 21, 133, 255};
constexpr SDL_Color Maroon = {128, 0, 0, 255};
constexpr SDL_Color PaleVioletRed = {219, 112, 147, 255};
constexpr SDL_Color LightPink = {255, 182, 193, 255};
constexpr SDL_Color MistyRose = {255, 228, 225, 255};
constexpr SDL_Color Wine = {114, 47, 55, 255};
constexpr SDL_Color Brick = {156, 102, 98, 255};
constexpr SDL_Color Rust = {183, 65, 14, 255};
constexpr SDL_Color Cherry = {222, 49, 99, 255};
constexpr SDL_Color Rose = {255, 0, 127, 255};
constexpr SDL_Color Coral = {255, 127, 80, 255};
constexpr SDL_Color Scarlet = {255, 36, 0, 255};

// ============================================================================
// ORANGES & BROWNS (The Warm Earth Tones)
// ============================================================================

constexpr SDL_Color Orange = {255, 165, 0, 255};
constexpr SDL_Color DarkOrange = {255, 140, 0, 255};
constexpr SDL_Color LightOrange = {255, 200, 124, 255};
constexpr SDL_Color OrangeYellow = {255, 165, 0, 255};
constexpr SDL_Color Chocolate = {210, 105, 30, 255};
constexpr SDL_Color Peru = {205, 133, 63, 255};
constexpr SDL_Color RosyBrown = {188, 143, 143, 255};
constexpr SDL_Color SaddleBrown = {139, 69, 19, 255};
constexpr SDL_Color Sienna = {160, 82, 45, 255};
constexpr SDL_Color BurlyWood = {222, 184, 135, 255};
constexpr SDL_Color Tan = {210, 180, 140, 255};
constexpr SDL_Color Khaki = {240, 230, 140, 255};
constexpr SDL_Color DarkKhaki = {189, 183, 107, 255};
constexpr SDL_Color Wheat = {245, 222, 179, 255};
constexpr SDL_Color Moccasin = {255, 228, 181, 255};
constexpr SDL_Color NavajoWhite = {255, 222, 173, 255};
constexpr SDL_Color Bisque = {255, 228, 196, 255};
constexpr SDL_Color Peach = {255, 218, 185, 255};
constexpr SDL_Color BlanchedAlmond = {255, 235, 205, 255};
constexpr SDL_Color Linen = {250, 240, 230, 255};
constexpr SDL_Color AntiqueWhite = {250, 235, 215, 255};
constexpr SDL_Color PapayaWhip = {255, 239, 213, 255};
constexpr SDL_Color Coffee = {111, 78, 55, 255};
constexpr SDL_Color Caramel = {184, 115, 51, 255};
constexpr SDL_Color SandyBrown = {244, 164, 96, 255};
constexpr SDL_Color DarkGoldenrod = {184, 134, 11, 255};
constexpr SDL_Color Goldenrod = {218, 165, 32, 255};

// ============================================================================
// YELLOWS & GOLDS (Sunshine & Precious)
// ============================================================================

constexpr SDL_Color Yellow = {255, 255, 0, 255};
constexpr SDL_Color Gold = {255, 215, 0, 255};
constexpr SDL_Color LightYellow = {255, 255, 224, 255};
constexpr SDL_Color LemonChiffon = {255, 250, 205, 255};
constexpr SDL_Color PaleGoldenrod = {238, 232, 170, 255};
constexpr SDL_Color Cornsilk = {255, 248, 220, 255};
constexpr SDL_Color FloralWhite = {255, 250, 240, 255};
constexpr SDL_Color Sepia = {112, 66, 20, 255};
constexpr SDL_Color Mustard = {255, 200, 124, 255};
constexpr SDL_Color Butter = {255, 245, 238, 255};

// ============================================================================
// GREENS (Forests, Jewels & Nature)
// ============================================================================

constexpr SDL_Color Green = {0, 128, 0, 255};
constexpr SDL_Color DarkGreen = {0, 100, 0, 255};
constexpr SDL_Color LimeGreen = {50, 205, 50, 255};
constexpr SDL_Color Lime = {0, 255, 0, 255};
constexpr SDL_Color ForestGreen = {34, 139, 34, 255};
constexpr SDL_Color SeaGreen = {46, 139, 87, 255};
constexpr SDL_Color MediumSeaGreen = {60, 179, 113, 255};
constexpr SDL_Color DarkSeaGreen = {143, 188, 143, 255};
constexpr SDL_Color LightSeaGreen = {32, 178, 170, 255};
constexpr SDL_Color MediumAquamarine = {102, 205, 170, 255};
constexpr SDL_Color Aquamarine = {127, 255, 212, 255};
constexpr SDL_Color MediumSpringGreen = {0, 250, 154, 255};
constexpr SDL_Color SpringGreen = {0, 255, 127, 255};
constexpr SDL_Color OliveDrab = {107, 142, 35, 255};
constexpr SDL_Color Olive = {128, 128, 0, 255};
constexpr SDL_Color PaleGreen = {152, 251, 152, 255};
constexpr SDL_Color LightGreen = {144, 238, 144, 255};
constexpr SDL_Color YellowGreen = {154, 205, 50, 255};
constexpr SDL_Color GreenYellow = {173, 255, 47, 255};
constexpr SDL_Color LawnGreen = {124, 252, 0, 255};
constexpr SDL_Color Chartreuse = {127, 255, 0, 255};
constexpr SDL_Color Honeydew = {240, 255, 240, 255};
constexpr SDL_Color DarkOliveGreen = {85, 107, 47, 255};
constexpr SDL_Color MintGreen = {152, 251, 152, 255};
constexpr SDL_Color PineGreen = {1, 121, 111, 255};
constexpr SDL_Color CeladonGreen = {0, 139, 101, 255};
constexpr SDL_Color Jade = {0, 168, 107, 255};
constexpr SDL_Color Emerald = {80, 200, 120, 255};

// ============================================================================
// CYANS, TEALS & BLUES (Water & Sky)
// ============================================================================

constexpr SDL_Color Cyan = {0, 255, 255, 255};
constexpr SDL_Color Aqua = {0, 255, 255, 255};
constexpr SDL_Color DarkCyan = {0, 139, 139, 255};
constexpr SDL_Color Teal = {0, 128, 128, 255};
constexpr SDL_Color DarkTurquoise = {0, 206, 209, 255};
constexpr SDL_Color MediumTurquoise = {72, 209, 204, 255};
constexpr SDL_Color Turquoise = {64, 224, 208, 255};
constexpr SDL_Color LightTurquoise = {175, 238, 238, 255};
constexpr SDL_Color PaleTurquoise = {175, 238, 238, 255};
constexpr SDL_Color Cadet = {95, 158, 160, 255};
constexpr SDL_Color SteelBlue = {70, 130, 180, 255};
constexpr SDL_Color LightSteelBlue = {176, 196, 222, 255};
constexpr SDL_Color PowderBlue = {176, 224, 230, 255};
constexpr SDL_Color CornflowerBlue = {100, 149, 237, 255};
constexpr SDL_Color SkyBlue = {135, 206, 235, 255};
constexpr SDL_Color LightSkyBlue = {135, 206, 250, 255};
constexpr SDL_Color DeepSkyBlue = {0, 191, 255, 255};
constexpr SDL_Color DodgerBlue = {30, 144, 255, 255};
constexpr SDL_Color RoyalBlue = {65, 105, 225, 255};
constexpr SDL_Color Blue = {0, 0, 255, 255};
constexpr SDL_Color DarkBlue = {0, 0, 139, 255};
constexpr SDL_Color MediumBlue = {0, 0, 205, 255};
constexpr SDL_Color LightBlue = {173, 216, 230, 255};
constexpr SDL_Color MidnightBlue = {25, 25, 112, 255};
constexpr SDL_Color Navy = {0, 0, 128, 255};
constexpr SDL_Color Indigo = {75, 0, 130, 255};
constexpr SDL_Color Azure = {240, 255, 255, 255};
constexpr SDL_Color AliceBlue = {240, 248, 255, 255};
constexpr SDL_Color GhostWhite = {248, 248, 255, 255};
constexpr SDL_Color LavenderBlue = {230, 230, 250, 255};
constexpr SDL_Color Lavender = {230, 230, 250, 255};
constexpr SDL_Color Ocean = {0, 119, 182, 255};
constexpr SDL_Color Abyss = {0, 33, 71, 255};
constexpr SDL_Color Lagoon = {0, 206, 209, 255};

// ============================================================================
// PURPLES & MAGENTAS (Mystic & Royal)
// ============================================================================

constexpr SDL_Color Purple = {128, 0, 128, 255};
constexpr SDL_Color Magenta = {255, 0, 255, 255};
constexpr SDL_Color Fuchsia = {255, 0, 255, 255};
constexpr SDL_Color DarkMagenta = {139, 0, 139, 255};
constexpr SDL_Color DarkViolet = {148, 0, 211, 255};
constexpr SDL_Color BlueViolet = {138, 43, 226, 255};
constexpr SDL_Color MediumOrchid = {186, 85, 211, 255};
constexpr SDL_Color MediumPurple = {147, 112, 219, 255};
constexpr SDL_Color Orchid = {218, 112, 214, 255};
constexpr SDL_Color Plum = {221, 160, 221, 255};
constexpr SDL_Color Violet = {238, 130, 238, 255};
constexpr SDL_Color Thistle = {216, 191, 216, 255};
constexpr SDL_Color GrayViolet = {169, 169, 169, 255};
constexpr SDL_Color MediumSlateBlue = {123, 104, 238, 255};
constexpr SDL_Color SlateBlue = {106, 90, 205, 255};
constexpr SDL_Color DarkSlateBlue = {72, 61, 139, 255};
constexpr SDL_Color GhostViolet = {199, 21, 133, 255};
constexpr SDL_Color Iris = {75, 0, 130, 255};
constexpr SDL_Color Amethyst = {153, 102, 204, 255};
constexpr SDL_Color Lavenderblush = {255, 240, 245, 255};
constexpr SDL_Color Grape = {108, 52, 131, 255};
constexpr SDL_Color Eggplant = {110, 29, 83, 255};
constexpr SDL_Color Mulberry = {198, 44, 125, 255};

// ============================================================================
// PINKS & PASTELS (Soft & Dreamy)
// ============================================================================

constexpr SDL_Color Pink = {255, 192, 203, 255};
constexpr SDL_Color LightPink2 = {255, 182, 193, 255};
constexpr SDL_Color HotPink2 = {255, 105, 180, 255};
constexpr SDL_Color PaleVioletRed2 = {219, 112, 147, 255};
constexpr SDL_Color Mauve = {224, 176, 255, 255};
constexpr SDL_Color Lilac = {200, 162, 200, 255};
constexpr SDL_Color Cotton = {255, 240, 245, 255};
constexpr SDL_Color Blush = {255, 228, 225, 255};
constexpr SDL_Color Peachpuff = {255, 218, 185, 255};
constexpr SDL_Color Cream = {255, 253, 208, 255};
constexpr SDL_Color Mint = {189, 224, 210, 255};
constexpr SDL_Color Honeydew2 = {240, 255, 240, 255};

// ============================================================================
// GRAYS & NEUTRALS (The Boring But Essential)
// ============================================================================

constexpr SDL_Color Gainsboro = {220, 220, 220, 255};
constexpr SDL_Color WhiteSmoke = {245, 245, 245, 255};
constexpr SDL_Color Snow = {255, 250, 250, 255};
constexpr SDL_Color Ivory = {255, 255, 240, 255};
constexpr SDL_Color Beige = {245, 245, 220, 255};
constexpr SDL_Color Seashell = {255, 245, 238, 255};
constexpr SDL_Color OldLace = {253, 245, 230, 255};
constexpr SDL_Color Silver = {192, 192, 192, 255};
constexpr SDL_Color DimGray = {105, 105, 105, 255};
constexpr SDL_Color SlateGray = {112, 128, 144, 255};
constexpr SDL_Color LightSlateGray = {119, 136, 153, 255};
constexpr SDL_Color DarkSlateGray = {47, 79, 79, 255};

// ============================================================================
// GAME-SPECIFIC FAVORITES (Curated for Game Dev)
// ============================================================================

constexpr SDL_Color GameBlack = {20, 20, 30, 255}; // Slightly blue-black
constexpr SDL_Color GameWhite = {245, 245, 250,
                                 255}; // Slight blue tint, easier on eyes
constexpr SDL_Color UIAccent = {100, 200, 255, 255};    // Classic game UI blue
constexpr SDL_Color HealthGreen = {100, 200, 100, 255}; // Health bar green
constexpr SDL_Color DamageRed = {255, 80, 80, 255};     // Damage/error red
constexpr SDL_Color SelectYellow = {255, 255, 100,
                                    255};          // UI selection highlight
constexpr SDL_Color ShadowBlack = {0, 0, 0, 100};  // Semi-transparent shadow
constexpr SDL_Color DebugGreen = {0, 255, 0, 200}; // Debug collision boxes
constexpr SDL_Color DebugRed = {255, 0, 0, 200};   // Debug trigger zones
constexpr SDL_Color DebugBlue = {0, 0, 255, 200};  // Debug cameras/zones
constexpr SDL_Color MagicPurple = {200, 100, 255, 255}; // Magic/special effects
constexpr SDL_Color PoisonGreen = {0, 200, 50, 255};    // Poison/toxic
constexpr SDL_Color FrostBlue = {100, 200, 255, 255};   // Frost/ice effects
constexpr SDL_Color FireOrange = {255, 150, 0, 255};    // Fire/heat effects
constexpr SDL_Color ElectricYellow = {255, 255, 100, 255}; // Electric/lightning
constexpr SDL_Color HolyWhite = {255, 255, 200, 255};      // Holy/blessed
constexpr SDL_Color ShadowPurple = {100, 50, 150, 255};    // Shadow/dark magic

// ============================================================================
// COLOR PAIRS (Contrasting duos for UI)
// ============================================================================

struct ColorPair {
  SDL_Color primary;
  SDL_Color secondary;
};

// Usage: auto pair = Tebya::Colors::DarkMode;
//        renderer.fillRect(rect, pair.primary);

inline constexpr ColorPair DarkMode = {
    {30, 30, 40, 255},   // Charcoal background
    {240, 240, 250, 255} // Bright text
};

inline constexpr ColorPair LightMode = {
    {245, 245, 250, 255}, // Off-white background
    {20, 20, 30, 255}     // Dark text
};

inline constexpr ColorPair CyberpunkMode = {
    {15, 15, 25, 255}, // Deep black
    {0, 255, 200, 255} // Neon cyan text
};

inline constexpr ColorPair RetroMode = {
    {51, 51, 51, 255},  // Retro gray
    {255, 200, 87, 255} // Retro orange
};

// ============================================================================
// UTILITY FUNCTIONS (Dark magic included)
// ============================================================================

// Lerp between two colors (smooth gradient transitions)
inline SDL_Color Lerp(SDL_Color a, SDL_Color b, float t) {
  t = (t < 0.0f) ? 0.0f : (t > 1.0f) ? 1.0f : t;
  return {static_cast<uint8_t>(a.r + (b.r - a.r) * t),
          static_cast<uint8_t>(a.g + (b.g - a.g) * t),
          static_cast<uint8_t>(a.b + (b.b - a.b) * t),
          static_cast<uint8_t>(a.a + (b.a - a.a) * t)};
}

// Adjust brightness (lighten/darken)
inline SDL_Color Brighten(SDL_Color color, float factor) {
  factor = (factor < 0.0f) ? 0.0f : factor;
  return {static_cast<uint8_t>(std::min(255.0f, color.r * factor)),
          static_cast<uint8_t>(std::min(255.0f, color.g * factor)),
          static_cast<uint8_t>(std::min(255.0f, color.b * factor)), color.a};
}

// Adjust alpha (transparency)
inline SDL_Color WithAlpha(SDL_Color color, uint8_t alpha) {
  color.a = alpha;
  return color;
}

// Invert color
inline SDL_Color Invert(SDL_Color color) {
  return {static_cast<uint8_t>(255 - color.r),
          static_cast<uint8_t>(255 - color.g),
          static_cast<uint8_t>(255 - color.b), color.a};
}

// Grayscale conversion
inline SDL_Color Grayscale(SDL_Color color) {
  uint8_t gray =
      static_cast<uint8_t>(0.299 * color.r + 0.587 * color.g + 0.114 * color.b);
  return {gray, gray, gray, color.a};
}

// Saturate/desaturate (0.0 = grayscale, 1.0 = normal, 2.0 = super vibrant)
inline SDL_Color Saturate(SDL_Color color, float factor) {
  SDL_Color gray = Grayscale(color);
  return Lerp(gray, color, factor);
}

// Mix two colors
inline SDL_Color Mix(SDL_Color a, SDL_Color b, float ratio = 0.5f) {
  return Lerp(a, b, ratio);
}

} // namespace tebya::Colors