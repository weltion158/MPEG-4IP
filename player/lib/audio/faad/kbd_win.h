/************************* MPEG-2 NBC Audio Decoder **************************
 *                                                                           *
"This software module was originally developed by
AT&T, Dolby Laboratories, Fraunhofer Gesellschaft IIS in the course of
development of the MPEG-2 NBC/MPEG-4 Audio standard ISO/IEC 13818-7,
14496-1,2 and 3. This software module is an implementation of a part of one or more
MPEG-2 NBC/MPEG-4 Audio tools as specified by the MPEG-2 NBC/MPEG-4
Audio standard. ISO/IEC  gives users of the MPEG-2 NBC/MPEG-4 Audio
standards free license to this software module or modifications thereof for use in
hardware or software products claiming conformance to the MPEG-2 NBC/MPEG-4
Audio  standards. Those intending to use this software module in hardware or
software products are advised that this use may infringe existing patents.
The original developer of this software module and his/her company, the subsequent
editors and their companies, and ISO/IEC have no liability for use of this software
module or modifications thereof in an implementation. Copyright is not released for
non MPEG-2 NBC/MPEG-4 Audio conforming products.The original developer
retains full right to use the code for his/her  own purpose, assign or donate the
code to a third party and to inhibit third party from using the code for non
MPEG-2 NBC/MPEG-4 Audio conforming products. This copyright notice must
be included in all copies or derivative works."
Copyright(c)1996.
 *                                                                           *
 ****************************************************************************/
/*
 * $Id: kbd_win.h,v 1.2 2002/01/09 22:25:41 wmay Exp $
 */

#ifndef _KBD_WIN_H_
#define _KBD_WIN_H_

#ifdef WIN_TABLE

#ifdef _MSC_VER
#pragma warning(disable:4305)
#endif

float kbd_long[] = {  /* IBLEN = 1024 */
    0.00029256153896361,
    0.00042998567353047,
    0.00054674074589540,
    0.00065482304299792,
    0.00075870195068747,
    0.00086059331713336,
    0.00096177541439010,
    0.0010630609410878,
    0.0011650036308132,
    0.0012680012194148,
    0.0013723517232956,
    0.0014782864109136,
    0.0015859901976719,
    0.0016956148252373,
    0.0018072876903517,
    0.0019211179405514,
    0.0020372007924215,
    0.0021556206591754,
    0.0022764534599614,
    0.0023997683540995,
    0.0025256290631156,
    0.0026540948920831,
    0.0027852215281403,
    0.0029190616715331,
    0.0030556655443223,
    0.0031950812943391,
    0.0033373553240392,
    0.0034825325586930,
    0.0036306566699199,
    0.0037817702604646,
    0.0039359150179719,
    0.0040931318437260,
    0.0042534609610026,
    0.0044169420066964,
    0.0045836141091341,
    0.0047535159544086,
    0.0049266858431214,
    0.0051031617390698,
    0.0052829813111335,
    0.0054661819693975,
    0.0056528008963682,
    0.0058428750739943,
    0.0060364413070882,
    0.0062335362436492,
    0.0064341963925079,
    0.0066384581386503,
    0.0068463577565218,
    0.0070579314215715,
    0.0072732152202559,
    0.0074922451586909,
    0.0077150571701162,
    0.0079416871213115,
    0.0081721708180857,
    0.0084065440099458,
    0.0086448423940363,
    0.0088871016184291,
    0.0091333572848345,
    0.0093836449507939,
    0.0096380001314086,
    0.0098964583006517,
    0.010159054892306,
    0.010425825300561,
    0.010696804880310,
    0.010972028947167,
    0.011251532777236,
    0.011535351606646,
    0.011823520630897,
    0.012116075003993,
    0.012413049837429,
    0.012714480198999,
    0.013020401111478,
    0.013330847551161,
    0.013645854446288,
    0.013965456675352,
    0.014289689065314,
    0.014618586389712,
    0.014952183366697,
    0.015290514656976,
    0.015633614861688,
    0.015981518520214,
    0.016334260107915,
    0.016691874033817,
    0.017054394638241,
    0.017421856190380,
    0.017794292885832,
    0.018171738844085,
    0.018554228105962,
    0.018941794631032,
    0.019334472294980,
    0.019732294886947,
    0.020135296106839,
    0.020543509562604,
    0.020956968767488,
    0.021375707137257,
    0.021799757987407,
    0.022229154530343,
    0.022663929872540,
    0.023104117011689,
    0.023549748833816,
    0.024000858110398,
    0.024457477495451,
    0.024919639522613,
    0.025387376602207,
    0.025860721018295,
    0.026339704925726,
    0.026824360347160,
    0.027314719170100,
    0.027810813143900,
    0.028312673876775,
    0.028820332832801,
    0.029333821328905,
    0.029853170531859,
    0.030378411455255,
    0.030909574956490,
    0.031446691733739,
    0.031989792322926,
    0.032538907094693,
    0.033094066251369,
    0.033655299823935,
    0.034222637668991,
    0.034796109465717,
    0.035375744712844,
    0.035961572725616,
    0.036553622632758,
    0.037151923373446,
    0.037756503694277,
    0.038367392146243,
    0.038984617081711,
    0.039608206651398,
    0.040238188801359,
    0.040874591269976,
    0.041517441584950,
    0.042166767060301,
    0.042822594793376,
    0.043484951661852,
    0.044153864320760,
    0.044829359199509,
    0.045511462498913,
    0.046200200188234,
    0.046895598002228,
    0.047597681438201,
    0.048306475753074,
    0.049022005960455,
    0.049744296827725,
    0.050473372873129,
    0.051209258362879,
    0.051951977308273,
    0.052701553462813,
    0.053458010319350,
    0.054221371107223,
    0.054991658789428,
    0.055768896059787,
    0.056553105340134,
    0.057344308777513,
    0.058142528241393,
    0.058947785320893,
    0.059760101322019,
    0.060579497264926,
    0.061405993881180,
    0.062239611611049,
    0.063080370600799,
    0.063928290700012,
    0.064783391458919,
    0.065645692125747,
    0.066515211644086,
    0.067391968650269,
    0.068275981470777,
    0.069167268119652,
    0.070065846295935,
    0.070971733381121,
    0.071884946436630,
    0.072805502201299,
    0.073733417088896,
    0.074668707185649,
    0.075611388247794,
    0.076561475699152,
    0.077518984628715,
    0.078483929788261,
    0.079456325589986,
    0.080436186104162,
    0.081423525056808,
    0.082418355827392,
    0.083420691446553,
    0.084430544593841,
    0.085447927595483,
    0.086472852422178,
    0.087505330686900,
    0.088545373642744,
    0.089592992180780,
    0.090648196827937,
    0.091710997744919,
    0.092781404724131,
    0.093859427187640,
    0.094945074185163,
    0.096038354392069,
    0.097139276107423,
    0.098247847252041,
    0.099364075366580,
    0.10048796760965,
    0.10161953075597,
    0.10275877119451,
    0.10390569492671,
    0.10506030756469,
    0.10622261432949,
    0.10739262004941,
    0.10857032915821,
    0.10975574569357,
    0.11094887329534,
    0.11214971520402,
    0.11335827425914,
    0.11457455289772,
    0.11579855315274,
    0.11703027665170,
    0.11826972461510,
    0.11951689785504,
    0.12077179677383,
    0.12203442136263,
    0.12330477120008,
    0.12458284545102,
    0.12586864286523,
    0.12716216177615,
    0.12846340009971,
    0.12977235533312,
    0.13108902455375,
    0.13241340441801,
    0.13374549116025,
    0.13508528059173,
    0.13643276809961,
    0.13778794864595,
    0.13915081676677,
    0.14052136657114,
    0.14189959174027,
    0.14328548552671,
    0.14467904075349,
    0.14608024981336,
    0.14748910466804,
    0.14890559684750,
    0.15032971744929,
    0.15176145713790,
    0.15320080614414,
    0.15464775426459,
    0.15610229086100,
    0.15756440485987,
    0.15903408475193,
    0.16051131859170,
    0.16199609399712,
    0.16348839814917,
    0.16498821779156,
    0.16649553923042,
    0.16801034833404,
    0.16953263053270,
    0.17106237081842,
    0.17259955374484,
    0.17414416342714,
    0.17569618354193,
    0.17725559732720,
    0.17882238758238,
    0.18039653666830,
    0.18197802650733,
    0.18356683858343,
    0.18516295394233,
    0.18676635319174,
    0.18837701650148,
    0.18999492360384,
    0.19162005379380,
    0.19325238592940,
    0.19489189843209,
    0.19653856928714,
    0.19819237604409,
    0.19985329581721,
    0.20152130528605,
    0.20319638069594,
    0.20487849785865,
    0.20656763215298,
    0.20826375852540,
    0.20996685149083,
    0.21167688513330,
    0.21339383310678,
    0.21511766863598,
    0.21684836451719,
    0.21858589311922,
    0.22033022638425,
    0.22208133582887,
    0.22383919254503,
    0.22560376720111,
    0.22737503004300,
    0.22915295089517,
    0.23093749916189,
    0.23272864382838,
    0.23452635346201,
    0.23633059621364,
    0.23814133981883,
    0.23995855159925,
    0.24178219846403,
    0.24361224691114,
    0.24544866302890,
    0.24729141249740,
    0.24914046059007,
    0.25099577217522,
    0.25285731171763,
    0.25472504328019,
    0.25659893052556,
    0.25847893671788,
    0.26036502472451,
    0.26225715701781,
    0.26415529567692,
    0.26605940238966,
    0.26796943845439,
    0.26988536478190,
    0.27180714189742,
    0.27373472994256,
    0.27566808867736,
    0.27760717748238,
    0.27955195536071,
    0.28150238094021,
    0.28345841247557,
    0.28542000785059,
    0.28738712458038,
    0.28935971981364,
    0.29133775033492,
    0.29332117256704,
    0.29530994257338,
    0.29730401606034,
    0.29930334837974,
    0.30130789453132,
    0.30331760916521,
    0.30533244658452,
    0.30735236074785,
    0.30937730527195,
    0.31140723343430,
    0.31344209817583,
    0.31548185210356,
    0.31752644749341,
    0.31957583629288,
    0.32162997012390,
    0.32368880028565,
    0.32575227775738,
    0.32782035320134,
    0.32989297696566,
    0.33197009908736,
    0.33405166929523,
    0.33613763701295,
    0.33822795136203,
    0.34032256116495,
    0.34242141494820,
    0.34452446094547,
    0.34663164710072,
    0.34874292107143,
    0.35085823023181,
    0.35297752167598,
    0.35510074222129,
    0.35722783841160,
    0.35935875652060,
    0.36149344255514,
    0.36363184225864,
    0.36577390111444,
    0.36791956434930,
    0.37006877693676,
    0.37222148360070,
    0.37437762881878,
    0.37653715682603,
    0.37870001161834,
    0.38086613695607,
    0.38303547636766,
    0.38520797315322,
    0.38738357038821,
    0.38956221092708,
    0.39174383740701,
    0.39392839225157,
    0.39611581767449,
    0.39830605568342,
    0.40049904808370,
    0.40269473648218,
    0.40489306229101,
    0.40709396673153,
    0.40929739083810,
    0.41150327546197,
    0.41371156127524,
    0.41592218877472,
    0.41813509828594,
    0.42035022996702,
    0.42256752381274,
    0.42478691965848,
    0.42700835718423,
    0.42923177591866,
    0.43145711524314,
    0.43368431439580,
    0.43591331247564,
    0.43814404844658,
    0.44037646114161,
    0.44261048926688,
    0.44484607140589,
    0.44708314602359,
    0.44932165147057,
    0.45156152598727,
    0.45380270770813,
    0.45604513466581,
    0.45828874479543,
    0.46053347593880,
    0.46277926584861,
    0.46502605219277,
    0.46727377255861,
    0.46952236445718,
    0.47177176532752,
    0.47402191254100,
    0.47627274340557,
    0.47852419517009,
    0.48077620502869,
    0.48302871012505,
    0.48528164755674,
    0.48753495437962,
    0.48978856761212,
    0.49204242423966,
    0.49429646121898,
    0.49655061548250,
    0.49880482394273,
    0.50105902349665,
    0.50331315103004,
    0.50556714342194,
    0.50782093754901,
    0.51007447028990,
    0.51232767852971,
    0.51458049916433,
    0.51683286910489,
    0.51908472528213,
    0.52133600465083,
    0.52358664419420,
    0.52583658092832,
    0.52808575190648,
    0.53033409422367,
    0.53258154502092,
    0.53482804148974,
    0.53707352087652,
    0.53931792048690,
    0.54156117769021,
    0.54380322992385,
    0.54604401469766,
    0.54828346959835,
    0.55052153229384,
    0.55275814053768,
    0.55499323217338,
    0.55722674513883,
    0.55945861747062,
    0.56168878730842,
    0.56391719289930,
    0.56614377260214,
    0.56836846489188,
    0.57059120836390,
    0.57281194173835,
    0.57503060386439,
    0.57724713372458,
    0.57946147043912,
    0.58167355327012,
    0.58388332162591,
    0.58609071506528,
    0.58829567330173,
    0.59049813620770,
    0.59269804381879,
    0.59489533633802,
    0.59708995413996,
    0.59928183777495,
    0.60147092797329,
    0.60365716564937,
    0.60584049190582,
    0.60802084803764,
    0.61019817553632,
    0.61237241609393,
    0.61454351160718,
    0.61671140418155,
    0.61887603613527,
    0.62103735000336,
    0.62319528854167,
    0.62534979473088,
    0.62750081178042,
    0.62964828313250,
    0.63179215246597,
    0.63393236370030,
    0.63606886099946,
    0.63820158877577,
    0.64033049169379,
    0.64245551467413,
    0.64457660289729,
    0.64669370180740,
    0.64880675711607,
    0.65091571480603,
    0.65302052113494,
    0.65512112263906,
    0.65721746613689,
    0.65930949873289,
    0.66139716782102,
    0.66348042108842,
    0.66555920651892,
    0.66763347239664,
    0.66970316730947,
    0.67176824015260,
    0.67382864013196,
    0.67588431676768,
    0.67793521989751,
    0.67998129968017,
    0.68202250659876,
    0.68405879146403,
    0.68609010541774,
    0.68811639993588,
    0.69013762683195,
    0.69215373826012,
    0.69416468671849,
    0.69617042505214,
    0.69817090645634,
    0.70016608447958,
    0.70215591302664,
    0.70414034636163,
    0.70611933911096,
    0.70809284626630,
    0.71006082318751,
    0.71202322560554,
    0.71398000962530,
    0.71593113172842,
    0.71787654877613,
    0.71981621801195,
    0.72175009706445,
    0.72367814394990,
    0.72560031707496,
    0.72751657523927,
    0.72942687763803,
    0.73133118386457,
    0.73322945391280,
    0.73512164817975,
    0.73700772746796,
    0.73888765298787,
    0.74076138636020,
    0.74262888961827,
    0.74449012521027,
    0.74634505600152,
    0.74819364527663,
    0.75003585674175,
    0.75187165452661,
    0.75370100318668,
    0.75552386770515,
    0.75734021349500,
    0.75915000640095,
    0.76095321270137,
    0.76274979911019,
    0.76453973277875,
    0.76632298129757,
    0.76809951269819,
    0.76986929545481,
    0.77163229848604,
    0.77338849115651,
    0.77513784327849,
    0.77688032511340,
    0.77861590737340,
    0.78034456122283,
    0.78206625827961,
    0.78378097061667,
    0.78548867076330,
    0.78718933170643,
    0.78888292689189,
    0.79056943022564,
    0.79224881607494,
    0.79392105926949,
    0.79558613510249,
    0.79724401933170,
    0.79889468818046,
    0.80053811833858,
    0.80217428696334,
    0.80380317168028,
    0.80542475058405,
    0.80703900223920,
    0.80864590568089,
    0.81024544041560,
    0.81183758642175,
    0.81342232415032,
    0.81499963452540,
    0.81656949894467,
    0.81813189927991,
    0.81968681787738,
    0.82123423755821,
    0.82277414161874,
    0.82430651383076,
    0.82583133844180,
    0.82734860017528,
    0.82885828423070,
    0.83036037628369,
    0.83185486248609,
    0.83334172946597,
    0.83482096432759,
    0.83629255465130,
    0.83775648849344,
    0.83921275438615,
    0.84066134133716,
    0.84210223882952,
    0.84353543682130,
    0.84496092574524,
    0.84637869650833,
    0.84778874049138,
    0.84919104954855,
    0.85058561600677,
    0.85197243266520,
    0.85335149279457,
    0.85472279013653,
    0.85608631890295,
    0.85744207377513,
    0.85879004990298,
    0.86013024290422,
    0.86146264886346,
    0.86278726433124,
    0.86410408632306,
    0.86541311231838,
    0.86671434025950,
    0.86800776855046,
    0.86929339605590,
    0.87057122209981,
    0.87184124646433,
    0.87310346938840,
    0.87435789156650,
    0.87560451414719,
    0.87684333873173,
    0.87807436737261,
    0.87929760257204,
    0.88051304728038,
    0.88172070489456,
    0.88292057925645,
    0.88411267465117,
    0.88529699580537,
    0.88647354788545,
    0.88764233649580,
    0.88880336767692,
    0.88995664790351,
    0.89110218408260,
    0.89223998355154,
    0.89337005407600,
    0.89449240384793,
    0.89560704148345,
    0.89671397602074,
    0.89781321691786,
    0.89890477405053,
    0.89998865770993,
    0.90106487860034,
    0.90213344783689,
    0.90319437694315,
    0.90424767784873,
    0.90529336288690,
    0.90633144479201,
    0.90736193669708,
    0.90838485213119,
    0.90940020501694,
    0.91040800966776,
    0.91140828078533,
    0.91240103345685,
    0.91338628315231,
    0.91436404572173,
    0.91533433739238,
    0.91629717476594,
    0.91725257481564,
    0.91820055488334,
    0.91914113267664,
    0.92007432626589,
    0.92100015408120,
    0.92191863490944,
    0.92282978789113,
    0.92373363251740,
    0.92463018862687,
    0.92551947640245,
    0.92640151636824,
    0.92727632938624,
    0.92814393665320,
    0.92900435969727,
    0.92985762037477,
    0.93070374086684,
    0.93154274367610,
    0.93237465162328,
    0.93319948784382,
    0.93401727578443,
    0.93482803919967,
    0.93563180214841,
    0.93642858899043,
    0.93721842438279,
    0.93800133327637,
    0.93877734091223,
    0.93954647281807,
    0.94030875480458,
    0.94106421296182,
    0.94181287365556,
    0.94255476352362,
    0.94328990947213,
    0.94401833867184,
    0.94474007855439,
    0.94545515680855,
    0.94616360137644,
    0.94686544044975,
    0.94756070246592,
    0.94824941610434,
    0.94893161028248,
    0.94960731415209,
    0.95027655709525,
    0.95093936872056,
    0.95159577885924,
    0.95224581756115,
    0.95288951509097,
    0.95352690192417,
    0.95415800874314,
    0.95478286643320,
    0.95540150607863,
    0.95601395895871,
    0.95662025654373,
    0.95722043049100,
    0.95781451264084,
    0.95840253501260,
    0.95898452980058,
    0.95956052937008,
    0.96013056625336,
    0.96069467314557,
    0.96125288290073,
    0.96180522852773,
    0.96235174318622,
    0.96289246018262,
    0.96342741296604,
    0.96395663512424,
    0.96448016037959,
    0.96499802258499,
    0.96551025571985,
    0.96601689388602,
    0.96651797130376,
    0.96701352230768,
    0.96750358134269,
    0.96798818295998,
    0.96846736181297,
    0.96894115265327,
    0.96940959032667,
    0.96987270976912,
    0.97033054600270,
    0.97078313413161,
    0.97123050933818,
    0.97167270687887,
    0.97210976208030,
    0.97254171033525,
    0.97296858709871,
    0.97339042788392,
    0.97380726825843,
    0.97421914384017,
    0.97462609029350,
    0.97502814332534,
    0.97542533868127,
    0.97581771214160,
    0.97620529951759,
    0.97658813664749,
    0.97696625939282,
    0.97733970363445,
    0.97770850526884,
    0.97807270020427,
    0.97843232435704,
    0.97878741364771,
    0.97913800399743,
    0.97948413132414,
    0.97982583153895,
    0.98016314054243,
    0.98049609422096,
    0.98082472844313,
    0.98114907905608,
    0.98146918188197,
    0.98178507271438,
    0.98209678731477,
    0.98240436140902,
    0.98270783068385,
    0.98300723078342,
    0.98330259730589,
    0.98359396579995,
    0.98388137176152,
    0.98416485063031,
    0.98444443778651,
    0.98472016854752,
    0.98499207816463,
    0.98526020181980,
    0.98552457462240,
    0.98578523160609,
    0.98604220772560,
    0.98629553785362,
    0.98654525677772,
    0.98679139919726,
    0.98703399972035,
    0.98727309286089,
    0.98750871303556,
    0.98774089456089,
    0.98796967165036,
    0.98819507841154,
    0.98841714884323,
    0.98863591683269,
    0.98885141615285,
    0.98906368045957,
    0.98927274328896,
    0.98947863805473,
    0.98968139804554,
    0.98988105642241,
    0.99007764621618,
    0.99027120032501,
    0.99046175151186,
    0.99064933240208,
    0.99083397548099,
    0.99101571309153,
    0.99119457743191,
    0.99137060055337,
    0.99154381435784,
    0.99171425059582,
    0.99188194086414,
    0.99204691660388,
    0.99220920909823,
    0.99236884947045,
    0.99252586868186,
    0.99268029752989,
    0.99283216664606,
    0.99298150649419,
    0.99312834736847,
    0.99327271939167,
    0.99341465251338,
    0.99355417650825,
    0.99369132097430,
    0.99382611533130,
    0.99395858881910,
    0.99408877049612,
    0.99421668923778,
    0.99434237373503,
    0.99446585249289,
    0.99458715382906,
    0.99470630587254,
    0.99482333656229,
    0.99493827364600,
    0.99505114467878,
    0.99516197702200,
    0.99527079784214,
    0.99537763410962,
    0.99548251259777,
    0.99558545988178,
    0.99568650233767,
    0.99578566614138,
    0.99588297726783,
    0.99597846149005,
    0.99607214437834,
    0.99616405129947,
    0.99625420741595,
    0.99634263768527,
    0.99642936685928,
    0.99651441948352,
    0.99659781989663,
    0.99667959222978,
    0.99675976040620,
    0.99683834814063,
    0.99691537893895,
    0.99699087609774,
    0.99706486270391,
    0.99713736163442,
    0.99720839555593,
    0.99727798692461,
    0.99734615798589,
    0.99741293077431,
    0.99747832711337,
    0.99754236861541,
    0.99760507668158,
    0.99766647250181,
    0.99772657705478,
    0.99778541110799,
    0.99784299521785,
    0.99789934972976,
    0.99795449477828,
    0.99800845028730,
    0.99806123597027,
    0.99811287133042,
    0.99816337566108,
    0.99821276804596,
    0.99826106735952,
    0.99830829226732,
    0.99835446122649,
    0.99839959248609,
    0.99844370408765,
    0.99848681386566,
    0.99852893944805,
    0.99857009825685,
    0.99861030750869,
    0.99864958421549,
    0.99868794518504,
    0.99872540702178,
    0.99876198612738,
    0.99879769870160,
    0.99883256074295,
    0.99886658804953,
    0.99889979621983,
    0.99893220065356,
    0.99896381655254,
    0.99899465892154,
    0.99902474256924,
    0.99905408210916,
    0.99908269196056,
    0.99911058634952,
    0.99913777930986,
    0.99916428468421,
    0.99919011612505,
    0.99921528709576,
    0.99923981087174,
    0.99926370054150,
    0.99928696900779,
    0.99930962898876,
    0.99933169301910,
    0.99935317345126,
    0.99937408245662,
    0.99939443202674,
    0.99941423397457,
    0.99943349993572,
    0.99945224136972,
    0.99947046956130,
    0.99948819562171,
    0.99950543049000,
    0.99952218493439,
    0.99953846955355,
    0.99955429477803,
    0.99956967087154,
    0.99958460793242,
    0.99959911589494,
    0.99961320453077,
    0.99962688345035,
    0.99964016210433,
    0.99965304978499,
    0.99966555562769,
    0.99967768861231,
    0.99968945756473,
    0.99970087115825,
    0.99971193791510,
    0.99972266620792,
    0.99973306426121,
    0.99974314015288,
    0.99975290181568,
    0.99976235703876,
    0.99977151346914,
    0.99978037861326,
    0.99978895983845,
    0.99979726437448,
    0.99980529931507,
    0.99981307161943,
    0.99982058811377,
    0.99982785549283,
    0.99983488032144,
    0.99984166903600,
    0.99984822794606,
    0.99985456323584,
    0.99986068096572,
    0.99986658707386,
    0.99987228737764,
    0.99987778757524,
    0.99988309324717,
    0.99988820985777,
    0.99989314275675,
    0.99989789718072,
    0.99990247825468,
    0.99990689099357,
    0.99991114030376,
    0.99991523098456,
    0.99991916772971,
    0.99992295512891,
    0.99992659766930,
    0.99993009973692,
    0.99993346561824,
    0.99993669950161,
    0.99993980547870,
    0.99994278754604,
    0.99994564960642,
    0.99994839547033,
    0.99995102885747,
    0.99995355339809,
    0.99995597263451,
    0.99995829002249,
    0.99996050893264,
    0.99996263265183,
    0.99996466438460,
    0.99996660725452,
    0.99996846430558,
    0.99997023850356,
    0.99997193273736,
    0.99997354982037,
    0.99997509249183,
    0.99997656341810,
    0.99997796519400,
    0.99997930034415,
    0.99998057132421,
    0.99998178052220,
    0.99998293025975,
    0.99998402279338,
    0.99998506031574,
    0.99998604495686,
    0.99998697878536,
    0.99998786380966,
    0.99998870197921,
    0.99998949518567,
    0.99999024526408,
    0.99999095399401,
    0.99999162310077,
    0.99999225425649,
    0.99999284908128,
    0.99999340914435,
    0.99999393596510,
    0.99999443101421,
    0.99999489571473,
    0.99999533144314,
    0.99999573953040,
    0.99999612126300,
    0.99999647788395,
    0.99999681059383,
    0.99999712055178,
    0.99999740887647,
    0.99999767664709,
    0.99999792490431,
    0.99999815465123,
    0.99999836685427,
    0.99999856244415,
    0.99999874231676,
    0.99999890733405,
    0.99999905832493,
    0.99999919608613,
    0.99999932138304,
    0.99999943495056,
    0.99999953749392,
    0.99999962968950,
    0.99999971218563,
    0.99999978560337,
    0.99999985053727,
    0.99999990755616,
    0.99999995720387
};


float kbd_short [] = {  /* 128 pt half window */
    4.3795702929468881e-005,
    0.00011867384265436617,
    0.0002307165763996192,
    0.00038947282760568383,
    0.00060581272288302553,
    0.00089199695169487453,
    0.0012617254423430522,
    0.0017301724373162003,
    0.0023140071937421476,
    0.0030313989666022221,
    0.0039020049735530842,
    0.0049469401815512024,
    0.0061887279335368318,
    0.0076512306364647726,
    0.0093595599562652423,
    0.011339966208377799,
    0.013619706891715299,
    0.016226894586323766,
    0.019190324717288168,
    0.022539283975960878,
    0.026303340480472455,
    0.030512117046644357,
    0.03519504922365594,
    0.040381130021856941,
    0.046098643518702249,
    0.052374889768730587,
    0.059235903660769147,
    0.066706170556282418,
    0.074808341703430481,
    0.083562952548726227,
    0.092988147159339674,
    0.1030994120216919,
    0.11390932249409955,
    0.12542730516149531,
    0.13765941926783826,
    0.15060816028651081,
    0.16427228853114245,
    0.17864668550988483,
    0.19372224048676889,
    0.20948576943658073,
    0.22591996826744942,
    0.24300340184133981,
    0.26071052995068139,
    0.27901177101369551,
    0.29787360383626599,
    0.3172587073594233,
    0.33712613787396362,
    0.35743154274286698,
    0.37812740923363009,
    0.39916334663203618,
    0.42048639939189658,
    0.4420413886774246,
    0.4637712792815169,
    0.4856175685594023,
    0.50752069370766872,
    0.52942045344797806,
    0.55125643994680196,
    0.57296847662071559,
    0.59449705734411495,
    0.61578378249506627,
    0.63677178724712891,
    0.65740615754163356,
    0.67763432925662526,
    0.69740646622548552,
    0.71667581294953808,
    0.73539901809352737,
    0.75353642514900732,
    0.77105232699609816,
    0.78791518148597028,
    0.80409778560147072,
    0.81957740622770781,
    0.83433586607383625,
    0.84835958382689225,
    0.86163956818294229,
    0.87417136598406997,
    0.88595496528524853,
    0.89699465477567619,
    0.90729884157670959,
    0.91687983002436779,
    0.92575356460899649,
    0.93393934077779084,
    0.94145948779657318,
    0.94833902830402828,
    0.95460531956280026,
    0.96028768170574896,
    0.96541701848104766,
    0.97002543610646474,
    0.97414586584250062,
    0.97781169577969584,
    0.98105641710392333,
    0.98391328975491177,
    0.98641503193166202,
    0.98859353733226141,
    0.99047962335771556,
    0.9921028127769449,
    0.99349115056397752,
    0.99467105680259038,
    0.9956672157341897,
    0.99650250022834352,
    0.99719793020823266,
    0.99777266288955657,
    0.99824401211201486,
    0.99862749357391212,
    0.99893689243401962,
    0.99918434952623147,
    0.99938046234161726,
    0.99953439696357238,
    0.99965400728430465,
    0.99974595807027455,
    0.99981584876278362,
    0.99986833527824281,
    0.99990724749057802,
    0.99993570051598468,
    0.99995619835942084,
    0.99997072890647543,
    0.9999808496399144,
    0.99998776381655818,
    0.99999238714961569,
    0.99999540529959718,
    0.99999732268176988,
    0.99999850325054862,
    0.99999920402413744,
    0.9999996021706401,
    0.99999981649545566,
    0.99999992415545547,
    0.99999997338493041,
    0.99999999295825959,
    0.99999999904096815
};

#endif /* WIN_TABLE */

#endif  /* _KBD_WIN_H_ */
