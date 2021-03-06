/**
 * @file dtile.c
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <utils/vec.h>
#include <display/dtile.h>
#include <d3v/object.h>

/**
 * Représentation d'une tuile.
 */
struct dtile {
    struct object *obj;
    int fish_count;
    int penguin;
};

/**
 * Afficher du texte.
 * @param x - Position x.
 * @param y - Position y.
 * @param z - Position z.
 * @param string - Texte à afficher.
 * @param t - Nombre de caractère.
 * @param espace - Espace entre deux caractères.
 */
static void
render_string(float x, float y, float z,
	      const char *string, int t, float espace)
{

    GLboolean b; // save lighting state and disable
    glGetBooleanv(GL_LIGHTING, &b);
    glDisable(GL_LIGHTING);

    //Desactivation car non supporté pour la coloration de Bitmap
    glDisable(GL_TEXTURE_2D);

    //Couleur du texte
    glColor3f(0.0, 0.0, 0.0);
    static int load = 0;
    static char *buf = NULL;
    if (!load) {

    }
	

    for (int i = 0; i < t; i++) {
	//Positionnement du caractère
	glRasterPos3f(x + espace * i, y, z);
	glBitmap(0 ,0, 0, 0, 0, 0, NULL);
	// Dessiner le caractère
	//glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
    }
    glColor3f(1.0, 1.0, 1.0);
    //Réactivation
    glEnable(GL_TEXTURE_2D);

    if (b)
	glEnable(GL_LIGHTING);
}

/**
 * Créé une tuile.
 * @param m - Model de la tuile.
 * @param t - Texture de la tuile.
 * @param pos - Position de la tuile.
 * @param rot - Orientation de la tuile.
 * @param scale - Echelle de la tuile.
 * @param fish_count - Nombre de poissons sur la tuile.
 * @return struct dtile * - La tuile.
 */
struct dtile* dtile_create(struct model *m, struct texture *t,
			   vec3 pos, double rot,
			   double scale, int fish_count)
{
    struct dtile *ti = malloc(sizeof(*ti));
    vec3 sca = { scale, scale, scale };
    vec3 rot__ = { 0., rot, 0. };
    ti->obj = d3v_object_create(m, t, pos, rot__, sca);
    ti->fish_count = fish_count;
    ti->penguin = -1;
    return ti;
}

/**
 * Dessiner la tuile. 
 * @param ti - La tuile.
 */
void dtile_draw(struct dtile* ti)
{
    if (!ti)
	return;
    if (!d3v_object_is_hidden(ti->obj)) {
	vec3 pos; //char str[15];
	d3v_object_get_position(ti->obj, &pos);
//	sprintf(str, "%d", ti->fish_count);
//	render_string(pos.x, pos.y + 0.2,pos.z, str,
//		      strlen(str), 0.15);
	d3v_object_draw(ti->obj);
    }
}

/**
 * Obtenir l'orientation de a tuile.
 * @param ti - La tuile.
 * @param pos - Position à envoyer.
 * @return double - Orientation en degré.
 */
void dtile_get_position(struct dtile *ti, vec3 *pos)
{
    d3v_object_get_position(ti->obj, pos);
}

/**
 * Cacher la tuile.
 * @param ti - La tuile.
 */
void dtile_hide(struct dtile *ti)
{
    d3v_object_hide(ti->obj);
}

/**
 * Révéler la tuile.
 * @param ti - La tuile.
 */
void dtile_reveal(struct dtile *ti)
{
    d3v_object_reveal(ti->obj);
}

/**
 * Libérer la mémoire occupée par la tuile.
 * @param ti - La tuile.
 */
void dtile_free(struct dtile *ti)
{
    d3v_object_free(ti->obj);
    free(ti);
}

int dtile_get_penguin(const struct dtile *ti)
{
    return ti->penguin;
}

void dtile_set_penguin(struct dtile *ti, int penguin_id)
{
    ti->penguin = penguin_id;
}
