#include <iostream>
#include "libmv-capi.h"
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

// typedef pthread_spinlock_t SpinLock;

// #define IB_MIPMAP_LEVELS	20
// #define IB_FILENAME_SIZE	1024

// #    define MEM_mallocN(size, str) ((void)str, malloc(size))
// #    define MEM_callocN(size, str) ((void)str, calloc(size, 1))
// #    define MEM_freeN(ptr) free(ptr)

// #define MAX_NAME 64

// /* MovieTrackingMarker->flag */
// enum {
//     MARKER_DISABLED    = (1 << 0),
//     MARKER_TRACKED     = (1 << 1),
//     MARKER_GRAPH_SEL_X = (1 << 2),
//     MARKER_GRAPH_SEL_Y = (1 << 3),
//     MARKER_GRAPH_SEL   = (MARKER_GRAPH_SEL_X | MARKER_GRAPH_SEL_Y)
// };

// /* MovieTrackingTrack->adjframes */
// enum {
//     TRACK_MATCH_KEYFRAME  = 0,
//     TRACK_MATCH_PREVFRAME = 1
// };

// #define INIT_MINMAX(min, max) {                                               \
// 		(min)[0] = (min)[1] = (min)[2] =  1.0e30f;                            \
// 		(max)[0] = (max)[1] = (max)[2] = -1.0e30f;                            \
// 	} (void)0
// #define INIT_MINMAX2(min, max) {                                              \
// 		(min)[0] = (min)[1] = 1.0e30f;                                        \
// 		(max)[0] = (max)[1] = -1.0e30f;                                       \
// 	} (void)0

// void minmax_v2v2_v2(float min[2], float max[2], const float vec[2])
// {
// 	if (min[0] > vec[0]) min[0] = vec[0];
// 	if (min[1] > vec[1]) min[1] = vec[1];

// 	if (max[0] < vec[0]) max[0] = vec[0];
// 	if (max[1] < vec[1]) max[1] = vec[1];
// }

// /* MovieTrackingTrack->algorithm_flag */
// enum {
// 	TRACK_ALGORITHM_FLAG_USE_BRUTE			= (1 << 0),
// 	TRACK_ALGORITHM_FLAG_USE_NORMALIZATION	= (1 << 2),
// 	TRACK_ALGORITHM_FLAG_USE_MASK			= (1 << 3)
// };

// // /* Grease-Pencil Annotations - 'DataBlock' */
// // typedef struct bGPdata {
// // 	ID id;					/* Grease Pencil data is */
	
// // 	/* saved Grease-Pencil data */
// // 	ListBase layers;		/* bGPDlayers */
// // 	int flag;				/* settings for this datablock */
	
// // 	/* not-saved stroke buffer data (only used during paint-session) 
// // 	 * 	- buffer must be initialized before use, but freed after 
// // 	 *	  whole paint operation is over
// // 	 */
// // 	short sbuffer_size;			/* number of elements currently in cache */
// // 	short sbuffer_sflag;		/* flags for stroke that cache represents */
// // 	void *sbuffer;				/* stroke buffer (can hold GP_STROKE_BUFFER_MAX) */
// // } bGPdata;

// /**
//  * \ingroup imbuf
//  * This is the abstraction of an image.  ImBuf is the basic type used for all
//  * imbuf operations.
//  *
//  * Also; add new variables to the end to save pain!
//  *
//  */
// typedef struct ImBuf {
//     struct ImBuf *next, *prev;	/**< allow lists of ImBufs, for caches or flipbooks */

//     /* dimensions */
//     int x, y;				/* width and Height of our image buffer.
//                                          * Should be 'unsigned int' since most formats use this.
//                                          * but this is problematic with texture math in imagetexture.c
//                                          * avoid problems and use int. - campbell */

//     unsigned char planes;	/* Active amount of bits/bitplanes */
//     int channels;			/* amount of channels in rect_float (0 = 4 channel default) */

//     /* flags */
//     int	flags;				/* Controls which components should exist. */
//     int	mall;				/* what is malloced internal, and can be freed */

//     /* pixels */
//     unsigned int *rect;		/* pixel values stored here */
//     float *rect_float;		/* floating point Rect equivalent
// 	                         * Linear RGB color space - may need gamma correction to
// 	                         * sRGB when generating 8bit representations */

//     /* resolution - pixels per meter */
//     double ppm[2];

//     /* tiled pixel storage */
//     int tilex, tiley;
//     int xtiles, ytiles;
//     unsigned int **tiles;

//     /* zbuffer */
//     int	*zbuf;				/* z buffer data, original zbuffer */
//     float *zbuf_float;		/* z buffer data, camera coordinates */

//     /* parameters used by conversion between byte and float */
//     float dither;				/* random dither value, for conversion from float -> byte rect */

//     /* mipmapping */
//     struct ImBuf *mipmap[IB_MIPMAP_LEVELS]; /* MipMap levels, a series of halved images */
//     int miptot, miplevel;

//     /* externally used data */
//     int index;						/* reference index for ImBuf lists */
//     int	userflags;					/* used to set imbuf to dirty and other stuff */
//     struct ImMetaData *metadata;	/* image metadata */
//     void *userdata;					/* temporary storage, only used by baking at the moment */

//     /* file information */
//     int	ftype;							/* file type we are going to save as */
//     char name[IB_FILENAME_SIZE];		/* filename associated with this image */
//     char cachename[IB_FILENAME_SIZE];	/* full filename used for reading from cache */

//     /* memory cache limiter */
//     struct MEM_CacheLimiterHandle_s *c_handle; /* handle for cache limiter */
//     int refcounter; /* reference counter for multiple users */

//     /* some parameters to pass along for packing images */
//     unsigned char *encodedbuffer;     /* Compressed image only used with png currently */
//     unsigned int   encodedsize;       /* Size of data written to encodedbuffer */
//     unsigned int   encodedbuffersize; /* Size of encodedbuffer */

//     /* color management */
//     struct ColorSpace *rect_colorspace;          /* color space of byte buffer */
//     struct ColorSpace *float_colorspace;         /* color space of float buffer, used by sequencer only */
//     unsigned int *display_buffer_flags;          /* array of per-display display buffers dirty flags */
//     struct ColormanageCache *colormanage_cache;  /* cache used by color management */
//     int colormanage_flag;
//     // rcti invalid_rect;

//     // /* information for compressed textures */
//     // struct DDSData dds_data;
// } ImBuf;

// /* makesdna ignores */
// #ifdef DNA_DEPRECATED_ALLOW
// /* allow use of deprecated items */
// #  define DNA_DEPRECATED
// #else
// #  ifndef DNA_DEPRECATED
// #    ifdef __GNUC__
// #      define DNA_DEPRECATED __attribute__ ((deprecated))
// #    else
// /* TODO, msvc & others */
// #      define DNA_DEPRECATED
// #    endif
// #  endif
// #endif

// struct MovieTrackingTrack;

// typedef struct MovieTrackingMarker {
//     float pos[2];   /* 2d position of marker on frame (in unified 0..1 space) */

//     /* corners of pattern in the following order:
//      *
//      *       Y
//      *       ^
//      *       | (3) --- (2)
//      *       |  |       |
//      *       |  |       |
//      *       |  |       |
//      *       | (0) --- (1)
//      *       +-------------> X
//      *
//      * the coordinates are stored relative to pos.
//      */
//     float pattern_corners[4][2];

//     /* positions of left-bottom and right-top corners of search area (in unified 0..1 units,
//      * relative to marker->pos
//      */
//     float search_min[2], search_max[2];

//     int framenr;    /* number of frame marker is associated with */
//     int flag;       /* Marker's flag (alive, ...) */
// } MovieTrackingMarker;


// typedef struct MovieTrackingTrack {
//     struct MovieTrackingTrack *next, *prev;

//     char name[64];  /* MAX_NAME */

//     /* ** setings ** */

//     /* positions of left-bottom and right-top corners of pattern (in unified 0..1 units,
//      * relative to marker->pos)
//      * moved to marker's corners since planar tracking implementation
//      */
//     float pat_min[2] DNA_DEPRECATED, pat_max[2] DNA_DEPRECATED;

//     /* positions of left-bottom and right-top corners of search area (in unified 0..1 units,
//      * relative to marker->pos
//      * moved to marker since affine tracking implementation
//      */
//     float search_min[2] DNA_DEPRECATED, search_max[2] DNA_DEPRECATED;

//     float offset[2];                    /* offset to "parenting" point */

//     /* ** track ** */
//     int markersnr;                  /* count of markers in track */
//     int last_marker;                /* most recently used marker */
//     MovieTrackingMarker *markers;   /* markers in track */

//     /* ** reconstruction data ** */
//     float bundle_pos[3];            /* reconstructed position */
//     float error;                    /* average track reprojection error */

//     /* ** UI editing ** */
//     int flag, pat_flag, search_flag;    /* flags (selection, ...) */
//     float color[3];                     /* custom color for track */

//     /* ** control how tracking happens */
//     short frames_limit;     /* number of frames to be tarcked during single tracking session (if TRACKING_FRAMES_LIMIT is set) */
//     short margin;           /* margin from frame boundaries */
//     short pattern_match;    /* re-adjust every N frames */

//     /* tracking parameters */
//     short motion_model;     /* model of the motion for this track */
//     int algorithm_flag;    /* flags for the tracking algorithm (use brute, use esm, use pyramid, etc */
//     float minimum_correlation;          /* minimal correlation which is still treated as successful tracking */

//     // struct bGPdata *gpd;        /* grease-pencil data */

//     /* Weight of this track.
//      *
//      * Weight defines how much the track affects on the final reconstruction,
//      * usually gets animated in a way so when track has just appeared it's
//      * weight is zero and then it gets faded up.
//      *
//      * Used to prevent jumps of the camera when tracks are appearing or
//      * disappearing.
//      */
//     float weight, pad;
// } MovieTrackingTrack;

// typedef struct TracksMap {
// 	char object_name[MAX_NAME];
// 	bool is_camera;

// 	int num_tracks;
// 	int customdata_size;

// 	char *customdata;
// 	MovieTrackingTrack *tracks;

// 	struct GHash *hash;

// 	int ptr;

// 	/* Spin lock is used to sync context during tracking. */
// 	SpinLock spin_lock;
// } TracksMap;

// typedef struct TrackContext {
//     /* the reference marker and cutout search area */
//     MovieTrackingMarker reference_marker;

//     /* keyframed patch. This is the search area */
//     float *search_area;
//     int search_area_height;
//     int search_area_width;
//     int framenr;

//     float *mask;
// } TrackContext;

// typedef struct MovieClipUser {
//     int framenr;    /* current frame number */
//     short render_size, render_flag;     /* proxy render size */
// } MovieClipUser;


// typedef struct MovieTrackingSettings {
//     int flag;

//     /* ** default tracker settings */
//     short default_motion_model;         /* model of the motion for this track */
//     short default_algorithm_flag;       /* flags for the tracking algorithm (use brute, use esm, use pyramid, etc */
//     float default_minimum_correlation;  /* minimal correlation which is still treated as successful tracking */
//     short default_pattern_size;         /* size of pattern area for new tracks */
//     short default_search_size;          /* size of search area for new tracks */
//     short default_frames_limit;         /* number of frames to be tarcked during single tracking session (if TRACKING_FRAMES_LIMIT is set) */
//     short default_margin;               /* margin from frame boundaries */
//     short default_pattern_match;        /* re-adjust every N frames */
//     short default_flag;                 /* default flags like color channels used by default */
//     float default_weight;               /* default weight of the track */

//     short motion_flag;      /* flags describes motion type */

//     /* ** common tracker settings ** */
//     short speed;            /* speed of tracking */

//     /* ** reconstruction settings ** */
//     int keyframe1 DNA_DEPRECATED,
//         keyframe2 DNA_DEPRECATED;   /* two keyframes for reconstruction initialization
//                                      * were moved to per-tracking object settings
//                                      */

//     int reconstruction_flag;

//     /* which camera intrinsics to refine. uses on the REFINE_* flags */
//     short refine_camera_intrinsics, pad2;

//     /* ** tool settings ** */

//     /* set scale */
//     float dist;                 /* distance between two bundles used for scene scaling */

//     /* cleanup */
//     int clean_frames, clean_action;
//     float clean_error;

//     /* set object scale */
//     float object_distance;      /* distance between two bundles used for object scaling */

//     int pad3;
// } MovieTrackingSettings;

// typedef struct MovieTrackingContext {
//     MovieClipUser user;
//     MovieClip *clip;
//     int clip_flag;

//     int frames, first_frame;
//     bool first_time;

//     MovieTrackingSettings settings;
//     TracksMap *tracks_map;

//     bool backwards, sequence;
//     int sync_frame;
// } MovieTrackingContext;


// void BKE_tracking_marker_pattern_minmax(const MovieTrackingMarker *marker, float min[2], float max[2])
// {
// 	INIT_MINMAX2(min, max);

// 	minmax_v2v2_v2(min, max, marker->pattern_corners[0]);
// 	minmax_v2v2_v2(min, max, marker->pattern_corners[1]);
// 	minmax_v2v2_v2(min, max, marker->pattern_corners[2]);
// 	minmax_v2v2_v2(min, max, marker->pattern_corners[3]);
// }

// MovieTrackingMarker *BKE_tracking_marker_get(MovieTrackingTrack *track, int framenr)
// {
//     int a = track->markersnr - 1;

//     if (!track->markersnr)
//         return NULL;

//     /* approximate pre-first framenr marker with first marker */
//     if (framenr < track->markers[0].framenr)
//         return &track->markers[0];

//     if (track->last_marker < track->markersnr)
//         a = track->last_marker;

//     if (track->markers[a].framenr <= framenr) {
//         while (a < track->markersnr && track->markers[a].framenr <= framenr) {
//             if (track->markers[a].framenr == framenr) {
//                 track->last_marker = a;

//                 return &track->markers[a];
//             }
//             a++;
//         }

//         /* if there's no marker for exact position, use nearest marker from left side */
//         return &track->markers[a - 1];
//     }
//     else {
//         while (a >= 0 && track->markers[a].framenr >= framenr) {
//             if (track->markers[a].framenr == framenr) {
//                 track->last_marker = a;

//                 return &track->markers[a];
//             }

//             a--;
//         }

//         /* if there's no marker for exact position, use nearest marker from left side */
//         return &track->markers[a];
//     }

//     return NULL;
// }

// MovieTrackingMarker *BKE_tracking_marker_get_exact(MovieTrackingTrack *track, int framenr)
// {
//     MovieTrackingMarker *marker = BKE_tracking_marker_get(track, framenr);

//     if (marker->framenr != framenr)
//         return NULL;

//     return marker;
// }


// /* compiler should inline */
// static float max_ff(const float a, const float b) { return b > a ? b : a; }


// /* returns false if marker crossed margin area from frame bounds */
// static bool tracking_check_marker_margin(MovieTrackingTrack *track, MovieTrackingMarker *marker,
//                                          int frame_width, int frame_height)
// {
//     float pat_min[2], pat_max[2];
//     float margin_left, margin_top, margin_right, margin_bottom;
//     float normalized_track_margin[2];

//     /* margin from frame boundaries */
//     BKE_tracking_marker_pattern_minmax(marker, pat_min, pat_max);

//     normalized_track_margin[0] = (float)track->margin / frame_width;
//     normalized_track_margin[1] = (float)track->margin / frame_height;

//     margin_left   = max_ff(-pat_min[0], normalized_track_margin[0]);
//     margin_top    = max_ff( pat_max[1], normalized_track_margin[1]);
//     margin_right  = max_ff( pat_max[0], normalized_track_margin[0]);
//     margin_bottom = max_ff(-pat_min[1], normalized_track_margin[1]);

//     /* do not track markers which are too close to boundary */
//     if (marker->pos[0] < margin_left || marker->pos[0] > 1.0f - margin_right ||
//         marker->pos[1] < margin_bottom || marker->pos[1] > 1.0f - margin_top)
//     {
//         return false;
//     }

//     return true;
// }

// void tracking_get_search_origin_frame_pixel(int frame_width, int frame_height,
//                                             const MovieTrackingMarker *marker,
//                                             float frame_pixel[2])
// {
// 	/* Get the lower left coordinate of the search window and snap to pixel coordinates */
// 	marker_unified_to_frame_pixel_coordinates(frame_width, frame_height, marker, marker->search_min, frame_pixel);
// 	frame_pixel[0] = (int)frame_pixel[0];
// 	frame_pixel[1] = (int)frame_pixel[1];
// }

// ImBuf *BKE_tracking_get_search_imbuf(ImBuf *ibuf, MovieTrackingTrack *track, MovieTrackingMarker *marker,
//                                      bool anchored, bool disable_channels)
// {
// 	ImBuf *searchibuf;
// 	int x, y, w, h;
// 	float search_origin[2];

// 	tracking_get_search_origin_frame_pixel(ibuf->x, ibuf->y, marker, search_origin);

// 	x = search_origin[0];
// 	y = search_origin[1];

// 	if (anchored) {
// 		x += track->offset[0] * ibuf->x;
// 		y += track->offset[1] * ibuf->y;
// 	}

// 	w = (marker->search_max[0] - marker->search_min[0]) * ibuf->x;
// 	h = (marker->search_max[1] - marker->search_min[1]) * ibuf->y;

// 	if (w <= 0 || h <= 0)
// 		return NULL;

// 	searchibuf = IMB_allocImBuf(w, h, 32, ibuf->rect_float ? IB_rectfloat : IB_rect);

// 	IMB_rectcpy(searchibuf, ibuf, 0, 0, x, y, w, h);

// 	if (disable_channels) {
// 		if ((track->flag & TRACK_PREVIEW_GRAYSCALE) ||
// 		    (track->flag & TRACK_DISABLE_RED)       ||
// 		    (track->flag & TRACK_DISABLE_GREEN)     ||
// 		    (track->flag & TRACK_DISABLE_BLUE))
// 		{
// 			disable_imbuf_channels(searchibuf, track, true);
// 		}
// 	}

// 	return searchibuf;
// }

// /* Get grayscale float search buffer for given marker and frame. */
// static float *track_get_search_floatbuf(ImBuf *ibuf, MovieTrackingTrack *track, MovieTrackingMarker *marker,
//                                         int *width_r, int *height_r)
// {
// 	ImBuf *searchibuf;
// 	float *gray_pixels;
// 	int width, height;

// 	searchibuf = BKE_tracking_get_search_imbuf(ibuf, track, marker, false, true);

// 	if (!searchibuf) {
// 		*width_r = 0;
// 		*height_r = 0;
// 		return NULL;
// 	}

// 	width = searchibuf->x;
// 	height = searchibuf->y;

// 	gray_pixels = MEM_callocN(width * height * sizeof(float), "tracking floatBuf");

// 	if (searchibuf->rect_float) {
// 		float_rgba_to_gray(searchibuf->rect_float, gray_pixels, width * height,
// 		                   0.2126f, 0.7152f, 0.0722f);
// 	}
// 	else {
// 		uint8_rgba_to_float_gray((unsigned char *)searchibuf->rect, gray_pixels, width * height,
// 		                         0.2126f, 0.7152f, 0.0722f);
// 	}

// 	IMB_freeImBuf(searchibuf);

// 	*width_r = width;
// 	*height_r = height;

// 	return gray_pixels;
// }

// /* Update track's reference patch (patch from which track is tracking from)
//  *
//  * Returns false if reference image buffer failed to load.
//  */
// static bool track_context_update_reference(MovieTrackingContext *context, TrackContext *track_context,
//                                            MovieTrackingTrack *track, MovieTrackingMarker *marker, int curfra,
//                                            int frame_width, int frame_height)
// {
//     MovieTrackingMarker *reference_marker = NULL;
//     ImBuf *reference_ibuf = NULL;
//     int width, height;

//     /* calculate patch for keyframed position */
//     reference_ibuf = tracking_context_get_reference_ibuf(context->clip, &context->user, context->clip_flag,
//                                                          track, curfra, context->backwards, &reference_marker);

//     if (!reference_ibuf)
//         return false;

//     track_context->reference_marker = *reference_marker;
    
//     if (track_context->search_area) {
//         MEM_freeN(track_context->search_area);
//     }

//     track_context->search_area = track_get_search_floatbuf(reference_ibuf, track, reference_marker, &width, &height);
//     track_context->search_area_height = height;
//     track_context->search_area_width = width;

//     if ((track->algorithm_flag & TRACK_ALGORITHM_FLAG_USE_MASK) != 0) {
//         if (track_context->mask)
//             MEM_freeN(track_context->mask);

//         track_context->mask = BKE_tracking_track_get_mask(frame_width, frame_height, track, marker);
//     }

//     IMB_freeImBuf(reference_ibuf);

//     return true;
// }

// /* Peform tracking from a reference_marker to destination_ibuf.
//  * Uses marker as an initial position guess.
//  *
//  * Returns truth if tracker returned success, puts result
//  * to dst_pixel_x and dst_pixel_y.
//  */
// static bool configure_and_run_tracker(ImBuf *destination_ibuf, MovieTrackingTrack *track,
//                                       MovieTrackingMarker *reference_marker, MovieTrackingMarker *marker,
//                                       float *reference_search_area, int reference_search_area_width,
//                                       int reference_search_area_height, float *mask,
//                                       double dst_pixel_x[5], double dst_pixel_y[5])
// {
//     /* To convert to the x/y split array format for libmv. */
//     double src_pixel_x[5], src_pixel_y[5];

//     /* Settings for the tracker */
//     libmv_TrackRegionOptions options = {0};
//     libmv_TrackRegionResult result;

//     float *patch_new;

//     int new_search_area_width, new_search_area_height;
//     int frame_width, frame_height;

//     bool tracked;

//     frame_width = destination_ibuf->x;
//     frame_height = destination_ibuf->y;

//     /* for now track to the same search area dimension as marker has got for current frame
//      * will make all tracked markers in currently tracked segment have the same search area
//      * size, but it's quite close to what is actually needed
//      */
//     patch_new = track_get_search_floatbuf(destination_ibuf, track, marker,
//                                           &new_search_area_width, &new_search_area_height);

//     /* configure the tracker */
//     tracking_configure_tracker(track, mask, &options);

//     /* convert the marker corners and center into pixel coordinates in the search/destination images. */
//     tracking_get_marker_coords_for_tracking(frame_width, frame_height, reference_marker, src_pixel_x, src_pixel_y);
//     tracking_get_marker_coords_for_tracking(frame_width, frame_height, marker, dst_pixel_x, dst_pixel_y);

//     if (patch_new == NULL || reference_search_area == NULL)
//         return false;

//     /* run the tracker! */
//     tracked = libmv_trackRegion(&options,
//                                 reference_search_area,
//                                 reference_search_area_width,
//                                 reference_search_area_height,
//                                 patch_new,
//                                 new_search_area_width,
//                                 new_search_area_height,
//                                 src_pixel_x, src_pixel_y,
//                                 &result,
//                                 dst_pixel_x, dst_pixel_y);

//     MEM_freeN(patch_new);

//     return tracked;
// }

// /* Track all the tracks from context one more frame,
//  * returns FALSe if nothing was tracked.
//  */
// bool BKE_tracking_context_step(MovieTrackingContext *context)
// {
//     ImBuf *destination_ibuf;
//     int frame_delta = context->backwards ? -1 : 1;
//     int curfra =  BKE_movieclip_remap_scene_to_clip_frame(context->clip, context->user.framenr);
//     int a, map_size;
//     bool ok = false;

//     int frame_width, frame_height;

//     map_size = tracks_map_get_size(context->tracks_map);

//     /* Nothing to track, avoid unneeded frames reading to save time and memory. */
//     if (!map_size)
//         return false;

//     /* Get an image buffer for frame we're tracking to. */
//     context->user.framenr += frame_delta;

//     destination_ibuf = BKE_movieclip_get_ibuf_flag(context->clip, &context->user,
//                                                    context->clip_flag, MOVIECLIP_CACHE_SKIP);
//     if (!destination_ibuf)
//         return false;

//     frame_width = destination_ibuf->x;
//     frame_height = destination_ibuf->y;

// #pragma omp parallel for private(a) shared(destination_ibuf, ok) if (map_size > 1)
//     for (a = 0; a < map_size; a++) {
//         TrackContext *track_context = NULL;
//         MovieTrackingTrack *track;
//         MovieTrackingMarker *marker;

//         tracks_map_get_indexed_element(context->tracks_map, a, &track, (void **)&track_context);

//         marker = BKE_tracking_marker_get_exact(track, curfra);

//         if (marker && (marker->flag & MARKER_DISABLED) == 0) {
//             bool tracked = false, need_readjust;
//             double dst_pixel_x[5], dst_pixel_y[5];

//             if (track->pattern_match == TRACK_MATCH_KEYFRAME)
//                 need_readjust = context->first_time;
//             else
//                 need_readjust = true;

//             /* do not track markers which are too close to boundary */
//             if (tracking_check_marker_margin(track, marker, frame_width, frame_height)) {
//                 if (need_readjust) {
//                     if (track_context_update_reference(context, track_context, track, marker,
//                                                        curfra, frame_width, frame_height) == false)
//                     {
//                         /* happens when reference frame fails to be loaded */
//                         continue;
//                     }
//                 }

//                 tracked = configure_and_run_tracker(destination_ibuf, track,
//                                                     &track_context->reference_marker, marker,
//                                                     track_context->search_area,
//                                                     track_context->search_area_width,
//                                                     track_context->search_area_height,
//                                                     track_context->mask,
//                                                     dst_pixel_x, dst_pixel_y);
//             }

//             BLI_spin_lock(&context->tracks_map->spin_lock);
//             tracking_insert_new_marker(context, track, marker, curfra, tracked,
//                                        frame_width, frame_height, dst_pixel_x, dst_pixel_y);
//             BLI_spin_unlock(&context->tracks_map->spin_lock);

//             ok = true;
//         }
//     }

//     IMB_freeImBuf(destination_ibuf);

//     context->first_time = false;
//     context->frames++;

//     return ok;
// }

int main(int argc, char *argv[])
{
    libmv_DetectOptions options = {0};
    libmv_Features *features = NULL;
    Mat im = imread(argv[1], 1);
    Mat im_resized;
    int feat_num = 0;
    if (argc < 2)
    {
        std::cout << "usage: " << argv[0] << " IMG" << std::endl;
        return 0;
    }
    namedWindow("haderner", 1);
    resize(im, im_resized, Size(im.cols>>1, im.rows>>1));
    std::cout << "w: " << im_resized.cols << "h: " << im_resized.rows << std::endl;
    options.detector = LIBMV_DETECTOR_HARRIS;
    options.margin = 2;
    options.min_distance = 50;
    options.harris_threshold = 1e-5;
    features = libmv_detectFeaturesByte(im_resized.data, im_resized.cols,
                                        im_resized.rows  , 3, &options);
    feat_num = libmv_countFeatures(features);
    std::cout << "features num: " << feat_num << endl;
    for (int i = 0; i < feat_num; ++i)
    {
        double x, y, score, size;
        libmv_getFeature(features, i, &x, &y, &score, &size);
        circle(im_resized, Point(x, y), 4, CV_RGB(0,255,0));
    }
    
    for (; ; )
    {
        imshow("haderner", im_resized);
        int key = waitKey(10);
        if (key == 27)
        {
            break;
        }
    }
    libmv_featuresDestroy(features);
    return 0;
}
