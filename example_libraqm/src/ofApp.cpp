//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//

#include "ofApp.h"

// This section defines FreeType error strings.
#undef __FTERRORS_H__
#define FT_ERRORDEF( e, v, s )  { e, s },
#define FT_ERROR_START_LIST     {
#define FT_ERROR_END_LIST       { 0, 0 } };
const struct {
    int          code;
    const char*  message;
} FT_Errors[] =
#include FT_ERRORS_H


std::string FT_ERROR_TO_STRING(int error)
{
    return std::to_string(FT_Errors[error].code) + ": " + FT_Errors[error].message;
}

void ofApp::setup()
{
    std::string codePoints = "😃😇😍😜😸🙈🐺🐰👽🐉💰🏡🎅🍪🍕🚀🚻💩📷📦1⃣2⃣3⃣4⃣5⃣6⃣7⃣8⃣9⃣0⃣💏👩‍❤️‍💋‍👨👨‍❤️‍💋‍👨👩‍❤️‍💋‍👩💑👩‍❤️‍👨👨‍❤️‍👨👩‍❤️‍👩👪👨‍👩‍👦👨‍👩‍👧👨‍👩‍👧‍👦👨‍👩‍👦‍👦👨‍👩‍👧‍👧👨‍👨‍👦👨‍👨‍👧👨‍👨‍👧‍👦👨‍👨‍👦‍👦👨‍👨‍👧‍👧👩‍👩‍👦👩‍👩‍👧👩‍👩‍👧‍👦👩‍👩‍👦‍👦👩‍👩‍👧‍👧👁‍🗨";

    const char *fontfile;
    const char *text;
    int i;
    int ret = 1;

    raqm_t *rq = NULL;
    raqm_glyph_t *glyphs = NULL;
    size_t count;
    raqm_direction_t dir;

    FT_Library ft_library = NULL;
    FT_Face face = NULL;
    FT_Error ft_error;

    std::string s = ofToDataPath("Roboto-Regular.ttf", true);

    std::cout << s << std::endl;
    std::cout << s.data() << std::endl;

    fontfile = s.data();

    std::cout << fontfile << std::endl;


//    text = "😃😇😍😜😸🙈🐺🐰👽🐉💰🏡🎅🍪🍕🚀🚻💩📷📦1⃣2⃣3⃣4⃣5⃣6⃣7⃣8⃣9⃣0⃣💏👩‍❤️‍💋‍👨👨‍❤️‍💋‍👨👩‍❤️‍💋‍👩💑👩‍❤️‍👨👨‍❤️‍👨👩‍❤️‍👩👪👨‍👩‍👦👨‍👩‍👧👨‍👩‍👧‍👦👨‍👩‍👦‍👦👨‍👩‍👧‍👧👨‍👨‍👦👨‍👨‍👧👨‍👨‍👧‍👦👨‍👨‍👦‍👦👨‍👨‍👧‍👧👩‍👩‍👦👩‍👩‍👧👩‍👩‍👧‍👦👩‍👩‍👦‍👦👩‍👩‍👧‍👧👁‍🗨";

    text = "h";

    ft_error = FT_Init_FreeType (&ft_library);
    if (ft_error)
    {
        std::cout << "0 ft_error" << std::endl;
        std::cout << FT_ERROR_TO_STRING(ft_error) << std::endl;
        goto final;
    }

    ft_error = FT_New_Face (ft_library, fontfile, 0, &face);

    if (ft_error)
    {
        std::cout << "1 ft_error " << ft_error << std::endl;
        std::cout << FT_ERROR_TO_STRING(ft_error) << std::endl;
        goto final;
    }

    ft_error = FT_Set_Char_Size(face, face->units_per_EM, 0, 0, 0);
    if (ft_error)
    {
        std::cout << "2 ft_error" << std::endl;
        std::cout << FT_ERROR_TO_STRING(ft_error) << std::endl;
        goto final;
    }

    dir = RAQM_DIRECTION_DEFAULT;

    rq = raqm_create();
    if (rq == NULL)
    {
        std::cout << "raqm_create" << std::endl;
        std::cout << FT_ERROR_TO_STRING(ft_error) << std::endl;
        goto final;
    }

    if (!raqm_set_text_utf8(rq, text, strlen (text)))
    {
        std::cout << "raqm_set_text_utf8" << std::endl;
        std::cout << FT_ERROR_TO_STRING(ft_error) << std::endl;
        goto final;
    }

    if (!raqm_set_freetype_face(rq, face))
    {
        std::cout << "raqm_set_freetype_face" << std::endl;
        std::cout << FT_ERROR_TO_STRING(ft_error) << std::endl;
        goto final;
    }

    if (!raqm_set_par_direction (rq, dir))
    {
        std::cout << "raqm_set_par_direction" << std::endl;
        std::cout << FT_ERROR_TO_STRING(ft_error) << std::endl;
        goto final;
    }

    if (!raqm_layout (rq))
    {
        std::cout << "raqm_layout" << std::endl;
        std::cout << FT_ERROR_TO_STRING(ft_error) << std::endl;
        goto final;
    }

    glyphs = raqm_get_glyphs (rq, &count);
    if (glyphs == NULL)
    {
        std::cout << "raqm_get_glyphs" << std::endl;
        std::cout << FT_ERROR_TO_STRING(ft_error) << std::endl;
        goto final;
    }

    for (i = 0; i < count; i++)
    {
        printf ("%d %d %d %d %d %d\n",
                glyphs[i].index,
                glyphs[i].x_offset,
                glyphs[i].y_offset,
                glyphs[i].x_advance,
                glyphs[i].y_advance,
                glyphs[i].cluster);
    }

    ret = 0;

    final:
    raqm_destroy (rq);
    FT_Done_Face (face);
    FT_Done_FreeType (ft_library);

    ofLogNotice() << "Exiting.";
    ofExit();
}
