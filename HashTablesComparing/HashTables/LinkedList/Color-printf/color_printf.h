#ifndef COLOR_PRINTF_H
#define COLOR_PRINTF_H

/// @brief An enum type
/// Output color variables
enum MY_COLOR
{
    DEFAULT_COLOR     = 0,  /**< Value for default output color */
    RED_COLOR         = 31, /**< Value for red output color     */
    GREEN_COLOR       = 32, /**< Value for green output color   */
    YELLOW_COLOR      = 33, /**< Value for yellow output color  */
    BLUE_COLOR        = 34, /**< Value for yellow output color  */
    MAGENTA_COLOR     = 35, /**< Value for yellow output color  */
    CYAN_COLOR        = 36, /**< Value for yellow output color  */
    WHITE_COLOR       = 37  /**< Value for yellow output color  */
};

/// @brief An enum type
/// Output format of text
enum FORMAT
{
    BOLD    = 1, /**< Value for bold text */
    REGULAR = 0 /**< Value for regular text */
};

/**
 * @brief Function print colorful text what sets with
            three parameters
 *
 * @param [in] color sets color (MY_COLOR) of text
 * @param [in] font sets font (FORMAT) of text
 * @param [in] format_line format line with % symbols (same as in printf)
 * next parameter is values that would insert in format_line
 */
int color_printf(MY_COLOR color, FORMAT font, const char * format_line, ...);

/**
 * @brief Function change color of console text what sets with
            two parameters
 *
 * @param color (enum MY_COLOR)
 * @param font (enum FORMAT)
 */
void style_selector(MY_COLOR color, FORMAT font);

#endif
