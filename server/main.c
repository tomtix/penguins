/**
 * @file
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>
#include <unistd.h>
#include <string.h>

#include <server/server.h>
#include <server/player.h>
#include <server/path.h>
#include <utils/log.h>
#include <utils/math.h>

#include "option.h"

#ifndef TEST

#define SERVER_LOG_FILE "server.log"
#define LOG_LEVEL       INFO_LOG__


/**
 * Stop le programme.
 * @param format - Les options souhaitées.
 * @param ... - Autres paramètres.
 */
static void die(const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    vfprintf(stderr, format, ap);
    exit(EXIT_FAILURE);
}

/**
 * Récupérer le format d'usage du programme.
 * @return const char * - Le format en chaine de caractères.
 */
const char *usage(void)
{
    return "usage: %s libmap_**.so TILE_COUNT MAX_FISH DIMENSION\n";
}

/**
 * Main principal du serveur.
 * @param argc - Nombre d'options au programme.
 * @param argv - Les options.
 * @return int - EXIT_SUCCESS si l'exécution c'est bien passée.
 */
int main(int argc, char *argv[])
{
    /* if (argc < 5) */
    /* 	die(usage(), argv[0]); */
    path_init(argv[0]);
    rand_seed();
    log_init(LOG_LEVEL, SERVER_LOG_FILE);
    struct opt opt;
    parse_options(argc, argv, &opt);
    server_init(opt.tile, opt.fish, opt.dim, opt.mapname);
    server_run();
    int winner = server_get_winner();
    log_print(PRINT_LOG__, "player %d also known as %s "
	      "won with a score of %d!\n", winner, player_get_name(winner),
	      player_get_player_score(winner));
    server_exit();
    log_exit();
    path_exit();
    return EXIT_SUCCESS;
}

#endif

/**
 * @mainpage Projet Penguin
 *
 * <p> Dans les commandes qui suivent, '.' fait référence au répertoire 'trunk'.</p>
 *
 * <h4> Installer le projet: </h4>
 *   <p> ./release.sh </p>
 *
 * <h4> Lancer le projet:</h4>
 *   <p>./install/server/peng_server MAP TILE_COUNT MAX_FISH DIMENSION</p>
 *   <ul>
 *     <li> MAP: Chemin d'accès à une librairie de générateur de cartes.<br>
 *	      (Elles sont installée dans ./install/server/map/) </li>
 *     <li> TILE_COUNT: un entier, nombre de tuiles valides, 
 *            où les pingouins stationneront. </li>
 *     <li> MAX_FISH: un entier, maximum de poissons sur une tuile. </li>
 *     <li> DIMENSION: Dimension du graphe, la façon dont les dimensions supérieures sont
 *	      traitées dépendent du générateur de cartes. </li>
 *   </ul>
 *
 * <h4> Lancer les tests: </h4>
 *   <p> Pour permetre les tests, le projet doit être compilé avec ./debug.sh<br>
 *	 (cmake release désactive les assertions)</p>
 *	
 *   <p> Se déplacer dans  ./build/debug/, lancer la commande "make check" </p>
 *
 */
