#include <algorithm>
#include <cassert>
#include <cmath>
#include <ctime>
#include <iomanip> 
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

#define STRINGIFY0(x) #x
#define STRINGIFY(x) STRINGIFY0(x)

constexpr std::uint64_t piece_hash_values[768] alignas(64) =
{
    0x01510564b3120641, 0x81d4176bde347ed0, 0x87bb68b4058d6c0e, 0x2657ac0ae9cfb089, 0x239bb0832ef29261, 0x59d1f0891d937542,
    0x7bf5a56b5193f6d1, 0xb01171984a82d54d, 0x684643adfab5dd36, 0x56581113fe97511d, 0x2750e3fa9ec1d77e, 0xd8437d4ac7495dff,
    0x58a65f4d978060a0, 0x3a3b82f9e5ac5de9, 0x84e70af5088a1209, 0x8b3a40f05d78df64, 0x50abb939d84a6026, 0xb78a7755ebe3e565,
    0xc066557972943f9a, 0x259df84b0a47c5e8, 0x828093ffd06a1e1d, 0xf14197c74415b39c, 0xc832ec8e3807bc28, 0x6829333466959dc0,
    0x1fae99f759989009, 0x228e7a20d3426dd2, 0xa68fceecf12c9f6e, 0xc3ac6465509ab297, 0x7c6715faa2c82db6, 0x9a922a5bed65a45f,
    0x21bc4985d9891f14, 0xdbba65e4cce516db, 0x168bc1ac8656f100, 0xb87964bab9fb01c8, 0xd4aa666d5d6aed6f, 0x6282a6d326cf4dd3,
    0x93bbaf24e730ca68, 0xae108384900df125, 0xe88157bb4310d894, 0xfa73dac1e0955aac, 0x44d834b4429548d5, 0xd97102339b797bc7,
    0xbd4a027657a3d40b, 0xd7ad8659afd827b2, 0x0bfe7f624ce63053, 0xfaec5ca7cb9ae651, 0x0827785fff637176, 0xfbed2a0e957bb521,
    0xedc57147531e0638, 0xf5438f94341590e7, 0xb65c5c791a4b22a5, 0x6af1d8c342571620, 0xc22f6304656edfa1, 0x668250c6d0c9ba29,
    0xf9563f62fe1a2986, 0xb388c9b3a5c8c817, 0xe4fb0da0fcfe9120, 0x2f70d87a5dc77f9e, 0x6cec6c1e73663162, 0x1774e45e8b41fe77,
    0x4a7512fae5056cd7, 0x778a407b931e0d10, 0x29f213a85324ff78, 0x39b1fd85666266d2, 0x28e5418a1d647893, 0xedbe1e7ed4e59d39,
    0x912d60d1c7310467, 0x320276f756354804, 0xf0d15dee2937cfb7, 0xfe66c5c1ece7da56, 0x7ff5d127c7637c98, 0x635a35864b616e95,
    0x3b7ff5332c916052, 0x60b441c681039925, 0x623f0ef9745357f7, 0x8e385524f0fee030, 0xc6558ac6f0e2f2b8, 0xff9ac67ea6add597,
    0x52d1d0845eb36202, 0x47458acad9057be0, 0x84216f9b80bd1f22, 0x74250c3e45b0c68c, 0x4d6b6df316d33a43, 0xc94ceb3403517aff,
    0xb2d5b8a79f7e8f0b, 0x1ecdd45a15070fbe, 0xb3dadee753266cc0, 0xbe53d1a47fcc874b, 0x73ed0f65273f6701, 0xe01b7e80cc003a38,
    0x65e952b821f47507, 0xd286cea65a93775b, 0x8a5fb38ca8847d26, 0xbd4e3862ea3944f3, 0x6a8dcd269863193f, 0x4337598bf7880af1,
    0x392861bedebfa307, 0x16e6415a14a3d428, 0x3375b23fad63615b, 0x5117b4c9a562d7f5, 0x6fee5dd92e02d606, 0xaccbdf3d9faeb9d5,
    0x6fcef16367915bc9, 0xf6bad1d14b341fda, 0xa1b783d18ec50f37, 0x499bef485300e8f5, 0x98fe80bf0496e3eb, 0xadfc4f96e26a5ab7,
    0xe2b0ed4905977281, 0x973c48c75fb999f7, 0xc23ee3f1354ccef9, 0x8f6fc65979ad2834, 0xd45600d23c57f0ce, 0x2b1084d79964c69f,
    0xa491e16684c8ec15, 0xcb0dd5e635ad3d67, 0xbeec5f1b166309ce, 0x3360f9966d55a43d, 0x078af4cf6104fce8, 0xf57a0fa91d9b35b1,
    0xb453cc82ae056760, 0x6647a9b607758562, 0x469bcfcace5e1fe2, 0x04152c1ee1d98ada, 0xd8bf1575c3478f56, 0x621243b3ed338663,
    0x1a4aac88992e89e7, 0x94b5b7c8dbe96476, 0x44d2c61679918c41, 0x453333a65affeb45, 0x877ad20baf7b780e, 0xf702da39c31fcd7e,
    0x01a58bf8b4cf1741, 0x51ad6cdc353b2e24, 0x435ab9182ca60b86, 0xaf5e9ae740c75cb2, 0x8c0b09c002858165, 0x65c9319e2b9de475,
    0xbdbd6796f98a3f18, 0x1bb6c455bd0fecd1, 0xec942cd0436357df, 0x4341b648b8b09eb5, 0xb71b2e0d9cb553cc, 0x9b7517502d370063,
    0xb187cdca15cdb533, 0x5cdf00802b4143b3, 0x6d90c827ff455de8, 0x9482d9c7b7157d3c, 0x7dcf88f29165a2b8, 0x7f38c2720ca4e751,
    0x5e717fdd22de6d9c, 0xa07db609449c7bba, 0xe668ada5b88b1e4d, 0xc6dbe293c52f0062, 0x8854a1bc2f80e158, 0x7fdb199438e77b63,
    0x99df87c5619e08b1, 0xe207a34f29afd1da, 0x9dd8218c8b7058d4, 0x14d4dac5564a6259, 0x91951b8f2fa61188, 0xf7b66f8da3b61ad1,
    0x15605b78b428db4c, 0x3f42707c036f7cd1, 0x7f5926e928569838, 0x1c9e99827b2d6099, 0xe33a8a008676c316, 0x3bb08b9f5cb23072,
    0xd05c1cfcabed8dc5, 0x3a14e044b71e52b9, 0x0cc6c4a45989311c, 0xafb03a0b442d74e3, 0x3524c18828f454d9, 0x171c6965cfdb3181,
    0x5c4b6cd2081248af, 0x4accbb4917b8f623, 0x8a02784fbdde85c8, 0xc32a3a4ee86baadb, 0xa230812412e2382c, 0xddfa5b53b7509279,
    0x6c3160a9772508f3, 0xf671893554f7b500, 0xe77fcfbe6af88f1b, 0x258658ba358c623c, 0x6516fe0dd347a3aa, 0xaee37e3a9a5e0b73,
    0x8cfa783ae3077176, 0x9cea69b36ad98573, 0xd513a19def5b5730, 0xf8c2027a2454d565, 0xdef5bff34a39c6ae, 0xb9b078405b1a0120,
    0xa52193bbc786eabb, 0xdbb9e96ce7794f1f, 0x8eceeb4160990c05, 0xc440b57ef9fa3c69, 0xb4329e512724b2fd, 0x0b703bbd9bedbd9f,
    0x285464cf7ed168c6, 0xcaabe79357398458, 0x0a48ce323e28c8f2, 0xf43e8d8939267703, 0x3a8ab7231a83156b, 0x20a72698a4016d0f,
    0xebf94c66fa4b8a7c, 0xeb43bd945cd9fdbf, 0xa21a4e3d047a6b8c, 0xacb26449c703b63e, 0x1eff980ddd7b0b6b, 0x4e73f4b3adfa97db,
    0xe1e95701094a99d7, 0xf554dc731963faaf, 0xc53c4761c6868c1b, 0x70c86d4c1f64e7f7, 0x7720a6919b003639, 0xe5899a07684c118c,
    0xff516cc925e7ad1c, 0xe21ae7692507eaaa, 0xfea5136a2544e49d, 0xd7ca22ad86837cc4, 0xab9f3e99a2183901, 0xfcbfe9696892a996,
    0x670ae19d64700bf8, 0xd7b0e0062a1c8d89, 0xc733362135bb62df, 0x7ffcadd0ccfba35d, 0x1687731f1682a050, 0x7d73d385542c51e8,
    0x6655450cb789a73a, 0x96d7b1dbe3be0834, 0xf69415a8209fea0a, 0x447df78306022926, 0x59af5641602c6f1f, 0x2909c84c90d1fbc9,
    0x641a859a67915b47, 0xc4d66647838111bd, 0x23c0550f496b18dc, 0x74d0dfbfb36e6c4e, 0x2a8171f446261884, 0xdf67aa84b9386950,
    0x876183a15882056a, 0x41e5b1f1d3ac62cd, 0xd75dea8cd3da9324, 0x29a5623c5a73b2c1, 0xf03495a745f57adc, 0x3677fee28f712777,
    0x7e079e625ebcd643, 0xfd9c7e3873fa4968, 0xc0b88969b10fea00, 0x162b32c51b4f274a, 0x8fa2fe4d6fe8749b, 0xfbaa61cb520b7d64,
    0xc9cd8ebe6dd058e6, 0x1e11558fdad4f19b, 0xa74add0d19e28b5e, 0xb0ff88a37b32e2aa, 0x9c4d477dc95d6c35, 0x553341f667a39262,
    0x410e2cd1551165af, 0x6348886902f0facd, 0xc09ce6b1ace5ac4a, 0x3174637eb153f231, 0x365dd77836997349, 0x4dbbe96960932d33,
    0x6f12002a6a3d6569, 0x4b180d5d0ac02e13, 0x82e5b0283d65d689, 0x840a38dcb08ed8f5, 0x404e1835a803077a, 0xf9ae829427d1c668,
    0x33b2b5e17dbb13c5, 0xf2de0ea2baccff67, 0x5ddfcfd969e05967, 0x2cebdef3012af72c, 0xc69fc0b7145fb7b1, 0xc385cb710987908f,
    0x78bcfd7a7998d4bd, 0x45436835c9e71530, 0xce5d083de2e45ad9, 0x16dadc0e83ea3c03, 0xb88c24af99ba6e4e, 0x0860e4f968817979,
    0x0b56f9f3735cb1e7, 0x6cfddd80edadfcb6, 0x52cd8835149de29a, 0x6cc7e1c786cfdc87, 0x584039c93af14c30, 0x27b216c4bd930044,
    0xb3d6b96f467d9ecc, 0x31a553f80b2e5022, 0x415f6790ac607d45, 0xb89849daf7b47e89, 0xf328d117d2abd052, 0x122b4562f53677e3,
    0x7347a87413a3d6d3, 0xf83d0675499b95c5, 0xb661cf20734bf9c3, 0xa2c90338026abe16, 0xfe63b8f7c28e55fd, 0xd7d61c7853480971,
    0x62ab139d86a25e05, 0x038104a92af36a08, 0x26dbea15f190ff8e, 0x76c503cdf19c1b34, 0x39493d7f95510fa6, 0x3de7677063d8ca4e,
    0x563224c4344b1f49, 0x88cac88522a207b1, 0x61186d8f83e2de0a, 0x57c78abab0b10468, 0x76fc69eb765a0ebd, 0xdb3bfe6ebca12b66,
    0x32b7c9b9aa5db3e0, 0x8cf3098608ae54c7, 0x6377bf779a22d35e, 0xb8ced088da41a64b, 0x7b9dfc4f457645a4, 0xe10f95ed42a71ca3,
    0x83d7c3bda0091ee9, 0x8a5eedead8bcee3f, 0x97bb2b8cd06054d5, 0xcace0493f56dde7a, 0x5e19557291ce761d, 0x35e2e331a00c7cc6,
    0x8e479e980b774ccd, 0xd81f9d6da98a7b75, 0x040fe9903e5ef705, 0xc84d7e7977177e99, 0xc1b3ca8fde57beff, 0x4d4c1bc43487042c,
    0xc1cfd0b9987d9c4e, 0xee952559b98f76dc, 0x58e9ab1fac68df56, 0x4778b24c35aa319a, 0xfab4b93c375e11ea, 0x4246b2f9dfd20f5f,
    0x0548db9b99a09f21, 0xb20deafb83f15dd4, 0xf1406b9b45ded409, 0x1e97c4b64a0b34dd, 0x0017f1c5c3522b0a, 0xabf8418bfa6b5e1e,
    0x85e4ed8013199ae5, 0x8a68fbff4cecbd2a, 0xc78dac74332fb46e, 0xcff4667a1a1b32b3, 0x4388ccd47fdab2a1, 0x1a2878fa90bca07d,
    0xb34de9654406e798, 0xe0eb5106073f363b, 0x36b914eede5fb749, 0xae1d8832c8feffe1, 0x6141f1727a406dd5, 0xe199bc4547707d95,
    0x921c3ecc23454d02, 0x4196b9da5ba5649b, 0xa292848e298ca43a, 0x97c102c99952c0e8, 0xa38eb4233b610314, 0xbe699659ed7646f5,
    0xad6f2838898aa8b2, 0x0a8aa05f619859a2, 0xd076986eedc21a10, 0x908f308a67c8e76d, 0xbf49e36c568564fd, 0xf1a377959a43dcbc,
    0x65462d59f03f0131, 0x30dc000c3fe2ead5, 0x730c7689a974b7ec, 0xd73663fa0953acec, 0x6bb33feb6de8e97e, 0x587d46787801c736,
    0xa0d15a6847936f7e, 0x54db8b2af187c3b5, 0x9894a6dd3c77975a, 0xad73d67c6908a76d, 0xc3695f0912b83595, 0x1c68ed3fa419ac88,
    0x347c6a8ec355f4d7, 0xf5c028c289dd3205, 0x12046064aa399811, 0xd36d43590abc4e6e, 0x54dcf2d55de9f391, 0x96b853638c5d0871,
    0xc35409044f5c84cf, 0x7f83a2320acc30c9, 0x64d9adc60f3bfc05, 0xc408fad04d9a11e3, 0x732630d9bb103d05, 0x531a6e3d82f3d416,
    0xe859e6cd20108912, 0x1ab7394bab5913b7, 0x579f8ef2e96611a2, 0x18146b5bdbafab0e, 0x42ab1933dbd07b82, 0x1285196969a0c079,
    0x2bb9c73591f544fb, 0x413ad7a94588be28, 0xe2b9dfa038807d18, 0x24e25f44ee1639e3, 0x33e6e8965807a894, 0xb7a68b705c5e4673,
    0xf6371889b5007823, 0x6b53aac298a1758c, 0xaa420beb73f09acc, 0x184e44bde5f8b8ba, 0x206dff9e2e890ef8, 0x9c51ba366f443c89,
    0xafee07e4f51e84e4, 0xd4cb621cc84e7e17, 0x45d3716ca0e46566, 0x1bdc68c72ff366c6, 0x3dc3cb59104ea82c, 0xd4afaa5fe015f0a2,
    0x08a552cf2da2b46a, 0x7a5e25ab6f18b9c4, 0x0531eef446fe556d, 0x1162d33a581e622f, 0xbff630abec73b189, 0x58e34710fb896fdf,
    0xbc11f1ee7c8b34a6, 0x914cc8ddc6718a74, 0x33ca89d4bd32e5de, 0x62289b78189341b1, 0x7d4f96c01f6dfd86, 0x103d2de1bb3239dd,
    0x4a9da385b1948bbe, 0x38114dc8904e2b87, 0xcf0c5db159581b7c, 0x7ced016125ebdd7f, 0x00c9ec7d58443ea6, 0x8e1d6d133326a703,
    0xeb61bdfb55aac5ce, 0xb46b905820f53b30, 0x77ec18cdd1cd8aaa, 0x9ae921fe5045708b, 0xd1ddfa303489ab17, 0x129b333e6795199a,
    0x7e99e8951b63df82, 0x596315c298109ea8, 0xb2508217459d17b4, 0x859812cc33079b3c, 0x6c395e3cd58d11b2, 0xfa02a4ab875a5560,
    0x4bdbde663bbe7cc9, 0x3c4bc55523f309ad, 0xda50a2246fe77f7f, 0x12e41c41fc699d34, 0x9d36833b865afadb, 0x7c70cf56810e2487,
    0x5f2e5448c7e1db40, 0x935dba9ac375e6b8, 0xe50bddfa9666ae46, 0x0286c3404f5a872c, 0x3cb559c257470a52, 0x59e11071919b1fa5,
    0x2fc50e5a1cb2e86d, 0x4f35299957c12713, 0x24e1be6df5dddda3, 0xf673311c4a452b78, 0x5cabfcc9e165edc0, 0x09069dc61cf29bdd,
    0xc1d7264959935930, 0xdff0b48f09c02048, 0xecf82df665f246b1, 0x285fdbde6c8d27f6, 0x5c8628fc46a5eb58, 0xc6f0a399e9ec120e,
    0x7fcf5a6da2e34abb, 0xb5ae639fe0aad3ce, 0x6b6a09cd605f93fc, 0xb9d41f3f5043a8e1, 0x6a1508558259c598, 0x1cfbb59d1a7ca022,
    0xc87347a4434e96a1, 0xf95e82d16982f593, 0x94fc506d56072bf4, 0x1c0aefa8f6bbbd51, 0x764f20d812ae1658, 0x5cc5810b7a019304,
    0xd2c9d1f3fe8df13c, 0x9bde4588069ee725, 0xe89785724d8f8d66, 0x1fd5d1a4fcca9ff3, 0x8fec8fddf1883ad4, 0xe19949224b1d6fa1,
    0xa2d6169b62d850d6, 0x527a09387a012705, 0xda8b1b81bd142ee2, 0xd7fff0e753a84b95, 0x71aaf744353c28fe, 0x77a05f8f79f106c1,
    0x8844b6bd81bdeb5d, 0xb7d16d1465a92053, 0x6f0fd42d7936770e, 0x10095c802492c52e, 0x32ed5f7c6db37fb2, 0x824247444670bb41,
    0xedcef59c8aa94e3d, 0xd67594b854b6c4a9, 0xa3b5bc9f8536b158, 0x4d8875f95f74ec35, 0x40ae95e924467ccb, 0x276572d8d3c9ef5f,
    0xcecd46d3f7b7e606, 0xfcfb59df3314fc09, 0x0796f38f7b9e49d7, 0x72fefe0a71ca4565, 0x335b71be16e149cd, 0x6c429fe882d260b1,
    0x37537f1e6a42326f, 0xa54c466e5db96a85, 0xe402b98e26ed7008, 0xcd7bab28019ff2e9, 0xc1b166f34a67450c, 0x77056cfbf831f334,
    0x0c250b6bd6664d7f, 0xa5923815ee4f3876, 0x83821c9c63e645b8, 0xaa57fa0e85e9113d, 0xd53f42575864f7ae, 0x318ca53b42583307,
    0xe270580326d06c4e, 0x816e33cbbb2bcd79, 0x53a4e6c83edf3537, 0xec7c8dc428f2482c, 0xdfebbeb180ff71d2, 0xc92401aa51f5e87b,
    0x1859f5024cadceaa, 0xf3307dd518b81b7b, 0x38fdc1defc462c80, 0x810d2fd02b491f2a, 0xc61fb2b319e5febd, 0x34d1d6418aeb2578,
    0x8cbd319efd10656f, 0xd3dc76b0d00cc1b6, 0x1c697617a4a5d854, 0x15828e6f6e2a1299, 0xd52f135c4e6aeea0, 0x161a2d5a6fd8bf29,
    0x991d064ca86b000e, 0x79a0169564f05393, 0x0d61d30dc376bb0e, 0x575d1bbec91550f9, 0x3453f646d374cece, 0xbcccef11beef7f30,
    0x744ab48e2f351459, 0xd7f19f5b1228f308, 0xfef029880216f38e, 0x7e29da0bb00e83dd, 0xa0f0602ca7efd42e, 0x9d9071951580e43b,
    0xb04a60af0af07ea9, 0x72dc9cadbcb081fa, 0xbf223d90236d759d, 0xfd494856cdc7b19f, 0x93ab676ef87a2080, 0xf83b12ace154d355,
    0xe1b81ac910b77093, 0x774ab091b4cbeebe, 0x30c0ae79085cd265, 0xd17699e97d1fce3e, 0x3feb203bd28d7f2e, 0x9adfd81576ade7f8,
    0x6c58d367a7eb4e34, 0x6119f91efe0c3de4, 0x6d5e1900fb0aa649, 0x9e7bc9ee19d5b789, 0x08cce53a9147e1b8, 0x4a2789780860bac6,
    0xe685e68cf55cc3fc, 0xf7b9d9e7ee14e182, 0x1dbfe3cb56fec5cd, 0xd295f95112eaef6d, 0xafa3c85ce80f8801, 0x8c987ad1279f07ff,
    0x598384fe32d5b4f5, 0x6dec90596cbbd00b, 0x260c6b7611b4b59b, 0x37ebd0b411341c86, 0x9c103247c56f0e41, 0x14de39948ced57a2,
    0x877e991707f57bae, 0x3f52868e03d1b6f1, 0xa6e1ce2622c71f5b, 0x53e37cca0afcccac, 0xf4ed4a1422c206a3, 0x2cb3a4613868790a,
    0x9887cafd5ce1fe18, 0x8bbed8f6bee2258a, 0x7e474fa402c9f501, 0xe059f501575b134a, 0xd26488c57047df0d, 0xd3309ef4af8409b9,
    0x5f8c71be8ef05c7c, 0x2895fc7ceca99785, 0x72740e79757f9879, 0xb81137761a2d7b0a, 0x2ef05e5be7c69f99, 0xc599345f1fb56385,
    0x5d78d741e7e5cbc6, 0xa53f767895a3fbff, 0xa688f9daa7335a02, 0x69e2b2179aab9995, 0xc61355ea21454f11, 0xccd71c536f0fc7aa,
    0x4a0a9f73c6701b94, 0x1f602a270bb4dd5c, 0x6577cd1ed01d43ee, 0x996ddd33c1414146, 0xbf0561b7d6ad9612, 0x3075f4c73eb6748b,
    0x8fd3d672d9ad9f06, 0x34a6cd38e87841a2, 0x770cda955dc08491, 0x5e97fb498b1e8797, 0x19ef4b0f283e53cb, 0xfc0677f91d847b40,
    0x5dcd0e935c902add, 0xb61f014da11b93b2, 0x43189f931fb501c8, 0x4738fe6be394a9b9, 0xfbdb071c16371e43, 0x2a5053f713c7e358,
    0x5bee0d828ebc4899, 0x7fc5e00d35641a39, 0x3b1f81be4d59ff1d, 0x693c49d341225283, 0x111bdd7024706454, 0xfcf811bdda0187c7,
    0xb027c84298c127be, 0x2d4a9c8d680981b0, 0xc6b65e144d526f97, 0x5de956adabcd5ad1, 0x6ed0a80944374c56, 0xd4ac9b75dadd55f7,
    0x9f314220f5476549, 0x9a02f756a0b46f64, 0xf434bbfaf6d5cf2c, 0x8be48c7ae01181e0, 0xcfbb8fc1feb539e9, 0x12f0c5a0d9136c02,
    0x901e3d63ec6a224f, 0xf93b035c1beddff4, 0xe0e1705c538c6b04, 0x7441d9b6453fff4f, 0x0eda1783ef43986b, 0xc620d0260d3db46c,
    0x50ef948d14e25bfd, 0xcca180e8d3cc76a4, 0xa83ff828a3a5b54c, 0xcd03f90f2d918145, 0xd5a69b33dcc332ba, 0xb6b1fed89a52fd4c,
    0x53b62aeafa0c2547, 0x5f4234206e66ed7b, 0x24e6fd40f7762ce0, 0xf69b31d058f360d6, 0xf51cbd6568cbcd35, 0x6d0f93df8d193a93,
    0xbb32dad5853c3d28, 0x9c5b253a7dc95097, 0x5917d4004a97863a, 0x0f3b7195999ae91b, 0x94025d89f894a025, 0x3e18f2e72b996380,
    0xd653adfa1028a144, 0x032b695b08dfbd4e, 0xdf290288de762f42, 0xa40e385f9e1804fa, 0xfc12600fb711560a, 0x584c05a3b0355250,
    0xa84a4a0a510f88ab, 0xd1ac4b877e4696e4, 0xb95bd67e18321358, 0x2fb17d493171c705, 0x4f5ea86009b5be6a, 0x60fb8a0a061e0118,
    0x277646c5eb4be657, 0xd607a405280f3be6, 0x251bf7da6277137b, 0x9e482d9a27c7a170, 0x4a5391a4de153ec8, 0xcb5e1648116a445a,
    0x95418bf7b2759bf7, 0xbe8b2827b4ef2a3d, 0x7c0db98a7ac6eafd, 0xac080a6ff6f0d5a6, 0x78b49a118f76271c, 0x475d9c904c7003b8,
    0x04ccc1879eb83af6, 0x1620aac495423e7e, 0x154502cbf3eaa265, 0x320acec449031c2d, 0x9c2b8ad087ac3683, 0xc09bb2c43b53ef5b,
    0x76c3f6d1bb902a57, 0x1e63873550db2540, 0xa44d878c822a56cb, 0x30eb70bfc1477fc3, 0xaae65612c9ee9076, 0xe7eaea04043c28eb,
    0x2af5523799412c1c, 0x650ea47f01808d2f, 0x10587dbb716a39eb, 0xcbcfaedcab7a46fd, 0x8dad0c854912c164, 0xbaf7573eaa177caa,
    0x818da97692130e21, 0x27dc36eb8cf43fec, 0xaa20119f4c666099, 0xe2a12323b2aa6e5d, 0x182d9dc931f0a566, 0x6e6dd60232f5e576,
    0xba97946fbfba1e38, 0x35937bd28ebe76e9, 0x28a915f1d9d58d6c, 0xf96fcb0c105cc10b, 0x5b16dadb7e6cc964, 0x25dce87c549a41e9,
    0x584d5722d02ff4ce, 0x6b0698a2aa74e257, 0x46f2a6e7c0a18ee5, 0x24734f106098b0fb, 0xd71bfae32fafec1c, 0x5ce7f8225994960f,
    0xccada96d539c4b08, 0x9f359f5042f13b1c, 0x2f7edf4f215ce4e1, 0x4900a0fe1c44d92d, 0xb2f1895a4c9a55d1, 0xab5db8b7f8fda59a,
    0x505d3dff750f8744, 0x4bca670804b56e63, 0x6ba15a764dbabae6, 0x2a394420ad317648, 0x11452f647ee77c26, 0xeb4517ab725d213b,
    0xcb2047e539d3cb8c, 0x1cd2920a1e895b73, 0x627fd7b2eabe5da4, 0xb988bafd5846aac0, 0x39ff916766c75e9f, 0xefab220ce48e2166,
    0x3ecf591c86acd6db, 0x97bd33422b355f6e, 0x2fc28c4735addc49, 0xb70596182b03f7ec, 0x639240b36307988b, 0x86569e83bab266cb,
    0x82f63e517458bc42, 0x1585552efb469be5, 0x215344ea9c3ebc19, 0x295f17b93c5c5071, 0xef195e8a953e749c, 0x3dea0cfc2487d580,
    0x211000128fff24f4, 0xfef664a4f694dcbc, 0xaff4d9977eb5d0bc, 0xdad28c1615e5ba24, 0xd7ef3078a8dd0d9f, 0x77253041eaad7ecb,
    0x10903ca1eec485bd, 0x5fc89bc729fabe49, 0xad14c7aaceee59a3, 0x3b9890e976a6171d, 0xbdbdf6d3f18d914a, 0x5e34ef48429e08cf,
};
constexpr std::uint64_t castling_hash_values[16] =
{
    0xb4566a5d395db94c, 0xf25c6f77e31ecf94, 0x7ffd385a1e918e47, 0xca9b42d79ede6fd7, 0x204cb560048e0cb4, 0xc6a6e14051d45deb,
    0x593d7f00f7da6689, 0xddbf9f9db2c82de7, 0x390559721e5d5bcc, 0xdc23d46cc5faf6a0, 0xc13a9f9161034413, 0x5404f90aafaf6b05,
    0xbffc7304dbffc888, 0x06afa28043a777ab, 0xa26c3d91f974eadc, 0x0e757fae49d52402,
};
constexpr std::uint64_t color_hash_values[2] =
{
    0x4cbf67ceecb3996c, 0x8cdc4ed1d4881ab5,
};

enum Color : std::uint8_t { WHITE, BLACK };

inline Color operator~(Color c) { return static_cast<Color>(c ^ 1); }
inline int rank_fwd(Color c) { return c == WHITE ? 8 : -8; }

enum PieceType : std::uint8_t { PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING };

enum Piece : std::uint8_t
{
    NONE,
    WPAWN = 1 << 3, WKNIGHT, WBISHOP, WROOK, WQUEEN, WKING,
    BPAWN = 1 << 4, BKNIGHT, BBISHOP, BROOK, BQUEEN, BKING,
};

inline Color color(Piece p) { return static_cast<Color>(p >> 4); }
inline PieceType type(Piece p) { return static_cast<PieceType>(p & 7); }
inline Piece piece(Color c, PieceType t) { return static_cast<Piece>((c == WHITE ? 1 << 3 : 1 << 4) | t); }

enum Castling : std::uint8_t { WQ = 1 << 0, WK = 1 << 1, BQ = 1 << 2, BK = 1 << 3 };

inline Castling& operator|=(Castling& lhs, Castling rhs) { return lhs = static_cast<Castling>(lhs | rhs); }
inline Castling& operator&=(Castling& lhs, Castling rhs) { return lhs = static_cast<Castling>(lhs & rhs); }
inline Castling operator~(Castling c) { return static_cast<Castling>(~static_cast<std::uint8_t>(c)); }

std::ostream& operator<<(std::ostream& out, Castling c)
{
    if (c)
    {
        if (c & WK)
            out << 'K';
        if (c & WQ)
            out << 'Q';
        if (c & BK)
            out << 'k';
        if (c & BQ)
            out << 'q';
    }
    else
        out << '-';
    return out;
}

enum Square : std::uint8_t { A1 = 0, H1 = 56, H8 = 63, NO_SQUARE = 0xff };

inline Square& operator+=(Square& lhs, int rhs) { return lhs = static_cast<Square>(lhs + rhs); }
inline Square& operator-=(Square& lhs, int rhs) { return lhs = static_cast<Square>(lhs - rhs); }
inline Square operator++(Square& lhs, int)
{
    Square r = lhs;
    lhs = static_cast<Square>(lhs + 1);
    return r;
}

inline Square square(int file, int rank)
{
    return static_cast<Square>(file + (rank << 3));
}

Square parse_square(std::string_view s)
{
    return square(s[0] - 'a', s[1] - '1');
}

std::ostream& operator<<(std::ostream& out, Square sq)
{
    if (sq == NO_SQUARE)
        out << '-';
    else
        out << static_cast<char>('a' + (sq & 7)) << static_cast<char>('1' + (sq >> 3));
    return out;
}

enum BitBoard : std::uint64_t { EMPTY = 0, ALL = ~0ULL };

inline BitBoard bb(Square s) { return static_cast<BitBoard>(1ULL << s); }
inline BitBoard& operator|=(BitBoard& lhs, Square rhs) { return lhs = static_cast<BitBoard>(lhs | bb(rhs)); }
inline BitBoard& operator|=(BitBoard& lhs, BitBoard rhs) { return lhs = static_cast<BitBoard>(lhs | rhs); }
inline BitBoard& operator&=(BitBoard& lhs, BitBoard rhs) { return lhs = static_cast<BitBoard>(lhs & rhs); }
inline BitBoard operator|(BitBoard lhs, BitBoard rhs) { return static_cast<BitBoard>(static_cast<uint64_t>(lhs) | rhs); }
inline BitBoard operator&(BitBoard lhs, Square rhs) { return static_cast<BitBoard>(static_cast<uint64_t>(lhs) & bb(rhs)); }
inline BitBoard operator&(BitBoard lhs, BitBoard rhs) { return static_cast<BitBoard>(static_cast<uint64_t>(lhs) & rhs); }
inline BitBoard operator<<(BitBoard lhs, int rhs) { return static_cast<BitBoard>(static_cast<uint64_t>(lhs) << rhs); }
inline BitBoard operator>>(BitBoard lhs, int rhs) { return static_cast<BitBoard>(static_cast<uint64_t>(lhs) >> rhs); }
inline BitBoard operator~(BitBoard b) { return static_cast<BitBoard>(~static_cast<std::uint64_t>(b)); }
inline BitBoard operator~(Square sq) { return ~bb(sq); }

inline Square first_square(BitBoard b)
{
    return static_cast<Square>(__builtin_ctzll(b));
}

inline Square pop(BitBoard& b)
{
    Square ret = first_square(b);
    b &= ~ret;
    return ret;
}

inline int popcount(BitBoard b) { return __builtin_popcountll(b); }

enum MoveType : std::uint8_t { EN_PASSANT = 1, CASTLING = 2, PROMOTION = 4, CAPTURE = 8, INVALID_TYPE = 15 };

inline MoveType& operator|=(MoveType& lhs, MoveType rhs) { return lhs = static_cast<MoveType>(lhs | rhs); }
inline MoveType& operator&=(MoveType& lhs, MoveType rhs) { return lhs = static_cast<MoveType>(lhs & rhs); }
inline MoveType operator|(MoveType lhs, MoveType rhs) { return lhs |= rhs; }
inline MoveType operator&(MoveType lhs, MoveType rhs) { return lhs &= rhs; }
inline MoveType operator~(MoveType m) { return static_cast<MoveType>(~static_cast<unsigned>(m)); }
inline PieceType promotion(MoveType m) { return static_cast<PieceType>(1 + (m & 3)); }
inline MoveType promotion_move(PieceType t) { return static_cast<MoveType>((t - 1) | PROMOTION); }

enum Move : std::uint16_t { NULL_MOVE = 0, FROM_TO_MASK = 0xfff, FROM_TO_SIZE = 0x1000, INVALID = 0xffff };

inline Move move(Square from, Square to, MoveType type) { return static_cast<Move>(from | to << 6 | type << 12); }
inline Square from(Move mv) { return static_cast<Square>(mv & 63); }
inline Square to(Move mv) { return static_cast<Square>((mv >> 6) & 63); }
inline MoveType type(Move mv) { return static_cast<MoveType>((mv >> 12) & 15); }

std::ostream& operator<<(std::ostream& out, Move mv)
{
    out << from(mv) << to(mv);
    if (type(mv) & PROMOTION)
    {
        switch (promotion(type(mv)))
        {
            case QUEEN: out << 'q'; break;
            case ROOK: out << 'r'; break;
            case BISHOP: out << 'b'; break;
            case KNIGHT: out << 'n'; break;
            default: break;
        }
    }
    return out;
}

#ifndef TUNE
constexpr
#endif
int material[6] = {100, 330, 368, 539, 1061, 100000};

#ifndef TUNE
constexpr
#endif
int piece_square_table[6][64] alignas(64) =
{
    {
        0, 0, 0, 0, 0, 0, 0, 0,
        7, 19, 10, -37, -12, 17, 31, -5,
        7, 24, 1, -3, 11, 8, 37, 1,
        9, 29, 9, 15, 30, 7, 19, 2,
        14, 28, 13, 31, 21, 16, 37, 8,
        65, 108, 54, 65, 78, 74, 118, 66,
        148, 163, 185, 106, 130, 157, 209, 169,
        0, 0, 0, 0, 0, 0, 0, 0,
    },
    {
        -146, -28, -17, -43, -32, -32, -18, -55,
        -54, -53, -41, 14, 15, -16, 5, -65,
        -47, -6, 8, 35, -21, 24, 5, -9,
        1, -7, 32, 34, 42, 45, 14, -2,
        -2, 21, 43, 68, 60, 54, 24, 57,
        16, 23, 48, 50, 37, 57, 28, -12,
        -47, -2, 20, -25, 0, 31, -15, -33,
        -163, -85, -9, 17, 30, -1, -8, -160,
    },
    {
        -59, -27, -23, -40, -56, -21, -70, -48,
        -28, 13, -34, -2, 9, -29, 1, -15,
        -50, 10, 16, 18, 11, 25, 12, -5,
        -17, 14, 24, 35, 30, 20, 25, -19,
        -11, 18, 31, 31, 31, 28, 15, 19,
        -4, 29, 37, 37, 18, 68, 56, 1,
        -54, 22, 23, -29, 13, 8, 32, -99,
        -2, -7, -13, -1, -18, -50, -58, 20,
    },
    {
        -44, -28, -15, 1, 9, -17, -29, -47,
        -28, -16, -3, -2, 6, -31, 1, -79,
        -30, 4, -18, -19, -5, -28, -7, -18,
        -8, 7, 11, -15, 1, -7, 17, -22,
        -3, 24, 32, 7, 27, 35, 36, 16,
        16, 40, 54, 42, 37, 32, 34, 10,
        37, 47, 47, 60, 47, 55, 10, 18,
        -3, 42, 25, 36, 29, 11, -4, -18,
    },
    {
        -4, -43, -34, -14, -45, 3, -18, -15,
        -102, -42, -4, -8, 8, 9, -60, 12,
        -13, 9, 8, -1, 4, 0, 13, -17,
        -8, -42, 31, -27, 12, 28, 3, -22,
        -4, 16, 30, -2, 37, 37, 7, -22,
        15, 20, 21, 30, 38, 56, 17, 15,
        -29, -18, 27, 14, 53, 25, -2, -37,
        -12, 23, 35, 74, 21, 41, 42, 42,
    },
    {
        18, 18, 33, -10, -7, 6, 38, 25,
        6, 47, 21, 5, -13, 13, 3, 12,
        -23, 38, 10, 0, -10, -4, 4, 8,
        4, 38, 29, 32, 26, 2, 0, -8,
        32, 36, 41, 62, 44, 27, -18, -6,
        2, 60, 68, 51, 40, 31, 21, -37,
        -72, -15, 34, 57, 67, 34, 51, 29,
        -161, -16, -56, -12, 18, -86, -114, -117,
    },
};

int piece_square_value(Square sq, Color c, PieceType t)
{
    unsigned flip = c == WHITE ? 0 : 56;
    return material[t] + piece_square_table[t][sq ^ flip];
}

struct Memo
{
    Piece moved;
    Piece captured;
    Castling castling;
    Square en_passant;
    int halfmove_clock;
};

struct Position
{
    Memo do_move(Move mv);
    void undo_move(Move mv, const Memo& memo);

    void parse(std::istream& fen);
    void reset();
    Move parse_move(std::string_view s) const;

    void debug(std::ostream& out);

    BitBoard all_bb() const { return color_bb[WHITE] | color_bb[BLACK]; }
    std::uint64_t hash() const { return piece_hash ^ castling_hash_values[castling] ^ color_hash_values[next]; }

    void clear(Square sq, Piece p) { clear(sq, color(p), type(p)); }
    void clear(Square sq, Color c, PieceType t);
    void set(Square sq, Piece p) { set(sq, color(p), type(p), p); }
    void set(Square sq, Color c, PieceType t) { set(sq, c, t, piece(c, t)); }
    void set(Square sq, Color c, PieceType t, Piece p);

    Piece squares[64];
    BitBoard color_bb[2];
    BitBoard type_bb[6];
    Color next;
    Castling castling;
    Square en_passant;
    int halfmove_clock;
    std::uint64_t piece_hash;
    int piece_square_values[2];
} position;

void Position::clear(Square sq, Color c, PieceType t)
{
    color_bb[c] &= ~sq;
    type_bb[t] &= ~sq;
    squares[sq] = NONE;
    piece_hash ^= piece_hash_values[sq | 64 * c | 128 * t];
    piece_square_values[c] -= piece_square_value(sq, c, t);
}

void Position::set(Square sq, Color c, PieceType t, Piece p)
{
    assert(t >= PAWN && t <= KING);
    color_bb[c] |= sq;
    type_bb[t] |= sq;
    squares[sq] = p;
    piece_hash ^= piece_hash_values[sq | 64 * c | 128 * t];
    piece_square_values[c] += piece_square_value(sq, c, t);
}

Memo Position::do_move(Move mv)
{
    Memo memo{squares[from(mv)], squares[to(mv)], castling, en_passant, halfmove_clock};
    ++halfmove_clock;

    if (mv)
    {
        MoveType mt = type(mv);
        if (mt & CAPTURE)
        {
            Square cap_sq = to(mv);
            if (mt == (EN_PASSANT | CAPTURE))
            {
                cap_sq = static_cast<Square>(cap_sq + rank_fwd(~next));
                memo.captured = squares[cap_sq];
            }

            clear(cap_sq, memo.captured);
            halfmove_clock = 0;
        }
        Piece moved = squares[from(mv)];
        clear(from(mv), moved);
        if (mt & PROMOTION)
            set(to(mv), next, promotion(mt));
        else
            set(to(mv), moved);
        en_passant = NO_SQUARE;

        if (type(moved) == PAWN)
        {
            halfmove_clock = 0;
            if (mt == EN_PASSANT)
                en_passant = static_cast<Square>(from(mv) + rank_fwd(next));
        }
        if (mt == CASTLING)
        {
            int rank = from(mv) & ~7;
            Square rook_from = static_cast<Square>(rank | (to(mv) < from(mv) ? 0 : 7));
            Square rook_to = static_cast<Square>(rank | (to(mv) < from(mv) ? 3 : 5));
            assert(type_bb[ROOK] & rook_from);
            clear(rook_from, next, ROOK);
            set(rook_to, next, ROOK);
            castling &= ~static_cast<Castling>(3 << (2 * next));
        }
        else if (castling)
        {
            if (type(moved) == KING)
                castling &= ~static_cast<Castling>(3 << (2 * next));
            else if (type(moved) == ROOK)
                castling &= ~static_cast<Castling>(((from(mv) & 1) ? WK : WQ) << (2 * next));
            if ((type(mv) & CAPTURE) && type(memo.captured) == ROOK)
                castling &= ~static_cast<Castling>(((to(mv) & 1) ? WK : WQ) << (2 * ~next));
        }
    }
    else
        en_passant = NO_SQUARE;

    next = ~next;
    return memo;
}

void Position::undo_move(Move mv, const Memo& memo)
{
    next = ~next;
    halfmove_clock = memo.halfmove_clock;
    en_passant = memo.en_passant;
    castling = memo.castling;

    if (mv)
    {
        clear(to(mv), squares[to(mv)]);
        set(from(mv), memo.moved);

        MoveType mt = type(mv);
        if (mt & CAPTURE)
        {
            Square cap_sq = to(mv);
            if (mt == (EN_PASSANT | CAPTURE))
                cap_sq = static_cast<Square>(cap_sq + rank_fwd(~next));
            set(cap_sq, memo.captured);
        }

        if (mt == CASTLING)
        {
            int rank = from(mv) & ~7;
            Square rook_from = static_cast<Square>(rank | (to(mv) < from(mv) ? 0 : 7));
            Square rook_to = static_cast<Square>(rank | (to(mv) < from(mv) ? 3 : 5));
            clear(rook_to, next, ROOK);
            set(rook_from, next, ROOK);
        }
    }
}

void Position::parse(std::istream& fen)
{
    reset();

    std::string token;
    fen >> token;

    Square sq = H1;

    for (char ch : token)
    {
        if (ch == '/')
            sq -= 16;
        else if (ch >= '1' && ch <= '8')
            sq += ch - '0';
        else
        {
            Piece p;
            switch (ch)
            {
                case 'P': p = WPAWN; break;
                case 'N': p = WKNIGHT; break;
                case 'B': p = WBISHOP; break;
                case 'R': p = WROOK; break;
                case 'Q': p = WQUEEN; break;
                case 'K': p = WKING; break;
                case 'p': p = BPAWN; break;
                case 'n': p = BKNIGHT; break;
                case 'b': p = BBISHOP; break;
                case 'r': p = BROOK; break;
                case 'q': p = BQUEEN; break;
                case 'k': p = BKING; break;
                default: p = NONE; break;
            }
            set(sq++, p);
        }
    }

    fen >> token;
    if (token == "w")
        next = WHITE;
    else if (token == "b")
        next = BLACK;

    fen >> token;
    castling = Castling{};
    for (char ch : token)
    {
        switch (ch)
        {
            case 'K': castling |= WK; break;
            case 'Q': castling |= WQ; break;
            case 'k': castling |= BK; break;
            case 'q': castling |= BQ; break;
        }
    }

    fen >> token;
    if (token == "-")
        en_passant = NO_SQUARE;
    else
        en_passant = parse_square(token);

    int fullmove_counter;
    fen >> halfmove_clock >> fullmove_counter;
}

void Position::reset()
{
    piece_hash = 0;
    for (BitBoard& b : color_bb)
        b = EMPTY;
    for (BitBoard& b : type_bb)
        b = EMPTY;
    for (Piece& p : squares)
        p = NONE;
    for (int& v : piece_square_values)
        v = 0;
}

Move Position::parse_move(std::string_view s) const
{
    Square from = parse_square(s.substr(0, 2));
    Square to = parse_square(s.substr(2, 2));

    MoveType mt{};
    if (s.length() > 4)
    {
        PieceType promotion{};
        switch (s[4])
        {
            case 'n': promotion = KNIGHT; break;
            case 'b': promotion = BISHOP; break;
            case 'r': promotion = ROOK; break;
            case 'q': promotion = QUEEN; break;
        }
        mt = promotion_move(promotion);
    }
    else if (type(squares[from]) == PAWN)
    {
        if (to == en_passant)
            mt = EN_PASSANT | CAPTURE;
        else if (std::abs(from - to) == 16)
            mt = EN_PASSANT;
    }
    else if (type(squares[from]) == KING)
    {
        if (std::abs((from & 7) - (to & 7)) > 1)
            mt = CASTLING;
    }

    if (squares[to])
        mt |= CAPTURE;
    return move(from, to, mt);
}

void Position::debug(std::ostream& out)
{
    out << "info string fen ";

    for (int rank = 7; rank >= 0; --rank)
    {
        int blanks = 0;

        for (int file = 0; file < 8; ++file)
        {
            Square sq = square(file, rank);
            if (squares[sq] == NONE)
            {
                ++blanks;
            }
            else
            {
                if (blanks)
                {
                    out << blanks;
                    blanks = 0;
                }
                switch (squares[sq])
                {
                    case WPAWN: out << 'P'; break;
                    case WKNIGHT: out << 'N'; break;
                    case WBISHOP: out << 'B'; break;
                    case WROOK: out << 'R'; break;
                    case WQUEEN: out << 'Q'; break;
                    case WKING: out << 'K'; break;
                    case BPAWN: out << 'p'; break;
                    case BKNIGHT: out << 'n'; break;
                    case BBISHOP: out << 'b'; break;
                    case BROOK: out << 'r'; break;
                    case BQUEEN: out << 'q'; break;
                    case BKING: out << 'k'; break;
                    default: break;
                }
            }
        }

        if (blanks)
        {
            out << blanks;
            blanks = 0;
        }
        if (rank > 0)
            out << '/';
    }

    out << ' ' << (next == WHITE ? 'w' : 'b') << ' ' << castling << ' ' << en_passant << ' ' << halfmove_clock << " 1\n";
}

static BitBoard knight_attack[64] alignas(64);
static BitBoard king_attack[64] alignas(64);
static BitBoard pawn_attack[2][64] alignas(64);
static BitBoard pawn_push[2][64] alignas(64);
static BitBoard pawn_double_push[2][64] alignas(64);
static BitBoard ray[64][8] alignas(64);

struct LineMask
{
    BitBoard full;
    BitBoard lower;
    BitBoard upper;

    LineMask() : full{}, lower{}, upper{} { }
    LineMask(BitBoard l, BitBoard u) : full{l | u}, lower{l}, upper{u} { }
};

static LineMask line_masks[64][4] alignas(64);

BitBoard offset_bitboard(int file, int rank, const std::pair<int, int> (&offsets)[8])
{
    BitBoard ret{};
    for (auto off : offsets)
    {
        if (file + off.first >= 0 && file + off.first <= 7 && rank + off.second >= 0 && rank + off.second <= 7)
            ret |= square(file + off.first, rank + off.second);
    }
    return ret;
}

void init_bitboards()
{
    constexpr std::pair<int, int> knight_offsets[8] = {{-2, -1}, {-1, -2}, {2, -1}, {-1, 2}, {-2, 1}, {1, -2}, {2, 1}, {1, 2}};
    constexpr std::pair<int, int> king_offsets[8] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
    constexpr std::pair<int, int> ray_offsets[8] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}};

    for (Square sq = A1; sq <= H8; sq++)
    {
        int file = sq & 7;
        int rank = sq >> 3;

        knight_attack[sq] = offset_bitboard(file, rank, knight_offsets);
        king_attack[sq] = offset_bitboard(file, rank, king_offsets);

        for (Color c : {WHITE, BLACK})
        {
            if (rank == (c == WHITE ? 7 : 0))
                continue;
            if (file > 0)
                pawn_attack[c][sq] |= static_cast<Square>(sq - 1 + rank_fwd(c));
            if (file < 7)
                pawn_attack[c][sq] |= static_cast<Square>(sq + 1 + rank_fwd(c));

            pawn_push[c][sq] = bb(static_cast<Square>(sq + rank_fwd(c)));

            if (rank == (c == WHITE ? 1 : 6))
                pawn_double_push[c][sq] = bb(static_cast<Square>(sq + 2 * rank_fwd(c)));
        }

        for (int i = 0; i < 8; ++i)
        {
            auto off = ray_offsets[i];
            int f = file + off.first;
            int r = rank + off.second;
            while (f >= 0 && f <= 7 && r >= 0 && r <= 7)
            {
                ray[sq][i] |= square(f, r);
                f += off.first;
                r += off.second;
            }
        }

        line_masks[sq][0] = {ray[sq][0], ray[sq][4]};
        line_masks[sq][1] = {ray[sq][6], ray[sq][2]};
        line_masks[sq][2] = {ray[sq][1], ray[sq][5]};
        line_masks[sq][3] = {ray[sq][7], ray[sq][3]};
    }
}

BitBoard line_attack(BitBoard blockers, const LineMask& lm)
{
    BitBoard lower = lm.lower & blockers;
    BitBoard upper = lm.upper & blockers;
    return static_cast<BitBoard>(lm.full & (upper ^ (upper - (0x8000000000000000ULL >> __builtin_clzll(lower | 1)))));
}

BitBoard bishop_attack(Square sq, BitBoard blockers)
{
    return line_attack(blockers, line_masks[sq][0])
        | line_attack(blockers, line_masks[sq][1]);
}

BitBoard rook_attack(Square sq, BitBoard blockers)
{
    return line_attack(blockers, line_masks[sq][2])
        | line_attack(blockers, line_masks[sq][3]);
}

BitBoard queen_attack(Square sq, BitBoard blockers)
{
    return bishop_attack(sq, blockers) | rook_attack(sq, blockers);
}

BitBoard attackers(Square sq, Color c)
{
    return position.color_bb[c] & (
        (pawn_attack[~c][sq] & position.type_bb[PAWN])
        | (knight_attack[sq] & position.type_bb[KNIGHT])
        | (bishop_attack(sq, position.all_bb()) & position.type_bb[BISHOP])
        | (rook_attack(sq, position.all_bb()) & position.type_bb[ROOK])
        | (queen_attack(sq, position.all_bb()) & position.type_bb[QUEEN])
        | (king_attack[sq] & position.type_bb[KING])
    );
}

struct alignas(16) Stack
{
    std::uint64_t key;
    Move killer_moves[2];
    Move prev_move;

    void save_killer(Move move);
};

void Stack::save_killer(Move move)
{
    if (move != killer_moves[0])
    {
        killer_moves[1] = killer_moves[0];
        killer_moves[0] = move;
    }
}

bool repetition(const Stack* stack)
{
    std::uint64_t current = stack[0].key;
    int count = 0;
    for (int i = 4; i < position.halfmove_clock; i += 2)
    {
        if (stack[-i].key == current)
        {
            ++count;
            if (count >= 2)
                return true;
        }
    }
    return false;
}

struct MoveHistory
{
    std::int16_t value;

    MoveHistory(std::int16_t v = -8192) : value{v} { }

    void hit(int n, bool cut)
    {
        value = static_cast<std::int16_t>(value - n * value / 8192 + (cut ? n : -n));
    }
};

static MoveHistory history[2][FROM_TO_SIZE] alignas(64);
static MoveHistory capture_history[30][64] alignas(64);

enum MoveGenType { START, BEST, CAPTURES, QUIETS, END };

struct alignas(4) RankedMove
{
    Move move;
    std::int16_t rank;
};

bool operator<(RankedMove lhs, RankedMove rhs)
{
    return lhs.rank > rhs.rank;
}

struct MoveGen
{
    MoveGenType wanted;
    MoveGenType generated;
    RankedMove moves[256];
    int count;
    int index;
    Move best_move;
    const Stack& stack;

    explicit MoveGen(MoveGenType w, Move best, const Stack& st)
        : wanted{w}, generated{}, moves{}, count{}, index{}, best_move{best}, stack{st} {}

    Move next();

    void generate();
    std::int16_t rank_capture(Move mv) const;
    std::int16_t rank_quiet(Move mv) const;
    template<PieceType Type> void generate_pieces(MoveGenType gen, BitBoard from_mask, BitBoard to_mask);
    template<PieceType Type> void generate_piece(MoveGenType gen, Square sq, BitBoard to_mask);
    void generate_targets(MoveGenType gen, Square sq, BitBoard targets);
    void generate_targets(Square sq, BitBoard targets, MoveType mt);
    void generate_pawn_targets(Square sq, BitBoard targets, MoveType mt);
    void generate_target(Square sq, Square target, MoveType mt);
    template<int Offset> void generate_castling(Square sq);
};

void MoveGen::generate_target(Square sq, Square target, MoveType mt)
{
    assert(!(target & ~63));
    Move mv = move(sq, target, mt);
    if (generated == BEST || mv != best_move)
        moves[count++] = {mv, (mt & CAPTURE) ? rank_capture(mv) : rank_quiet(mv)};
}

void MoveGen::generate_targets(Square sq, BitBoard targets, MoveType mt)
{
    while (targets)
        generate_target(sq, pop(targets), mt);
}

void MoveGen::generate_pawn_targets(Square sq, BitBoard targets, MoveType mt)
{
    if ((sq >> 3) == (position.next == WHITE ? 6 : 1))
    {
        for (PieceType t : {QUEEN, ROOK, BISHOP, KNIGHT})
            generate_targets(sq, targets, promotion_move(t) | mt);
    }
    else
        generate_targets(sq, targets, mt);
}

void MoveGen::generate_targets(MoveGenType gen, Square sq, BitBoard targets)
{
    if (gen == CAPTURES)
        generate_targets(sq, targets & position.color_bb[~position.next], CAPTURE);
    if (gen == QUIETS)
        generate_targets(sq, targets & ~position.all_bb(), {});
}

template<int Offset> void MoveGen::generate_castling(Square sq)
{
    int rank = sq >> 3;
    Square rook_from = square(Offset < 0 ? 0 : 7, rank);
    if (!(line_attack(position.all_bb(), line_masks[sq][2]) & rook_from))
        return;

    for (int i = 0; i <= 2; i++)
    {
        Square s = square(4 + i * Offset, rank);
        if (attackers(s, ~position.next))
            return;
    }

    generate_target(sq, square(4 + 2 * Offset, rank), CASTLING);
}

template<PieceType Type> void MoveGen::generate_piece(MoveGenType gen, Square sq, BitBoard to_mask)
{
    if (Type == PAWN)
    {
        if (gen == CAPTURES)
        {
            generate_pawn_targets(sq, pawn_attack[position.next][sq] & position.color_bb[~position.next] & to_mask, CAPTURE);
            if (position.en_passant != NO_SQUARE && (pawn_attack[position.next][sq] & position.en_passant & to_mask))
                generate_target(sq, position.en_passant, EN_PASSANT | CAPTURE);
        }
        if (gen == QUIETS)
        {
            BitBoard push = pawn_push[position.next][sq] & ~position.all_bb();
            if (push)
            {
                generate_pawn_targets(sq, push & to_mask, {});
                generate_targets(sq, pawn_double_push[position.next][sq] & ~position.all_bb() & to_mask, EN_PASSANT);
            }
        }
    }
    else if (Type == KNIGHT)
        generate_targets(gen, sq, knight_attack[sq] & to_mask);
    else if (Type == BISHOP)
        generate_targets(gen, sq, bishop_attack(sq, position.all_bb()) & to_mask);
    else if (Type == ROOK)
        generate_targets(gen, sq, rook_attack(sq, position.all_bb()) & to_mask);
    else if (Type == QUEEN)
        generate_targets(gen, sq, queen_attack(sq, position.all_bb()) & to_mask);
    else if (Type == KING)
    {
        generate_targets(gen, sq, king_attack[sq] & to_mask);
        if (gen == QUIETS && (to_mask & ~king_attack[sq]))
        {
            if (position.castling & (WQ << (2 * position.next)))
                generate_castling<-1>(sq);
            if (position.castling & (WK << (2 * position.next)))
                generate_castling<1>(sq);
        }
    }
}

template<PieceType Type> void MoveGen::generate_pieces(MoveGenType gen, BitBoard from_mask, BitBoard to_mask)
{
    BitBoard pieces = position.color_bb[position.next] & position.type_bb[Type] & from_mask;
    while (pieces)
        generate_piece<Type>(gen, pop(pieces), to_mask);
}

std::int16_t MoveGen::rank_capture(Move mv) const
{
    return static_cast<std::int16_t>(8192 * (type(position.squares[to(mv)]) - 3) +
            capture_history[6 * type(position.squares[to(mv)]) + type(position.squares[from(mv)])][to(mv)].value);
}

std::int16_t MoveGen::rank_quiet(Move mv) const
{
    std::int16_t rank = history[position.next][mv & FROM_TO_MASK].value;
    if (mv == stack.killer_moves[0] || mv == stack.killer_moves[1])
        rank += 16354;
    return rank;
}

void MoveGen::generate()
{
    generated = static_cast<MoveGenType>(generated + 1);
    MoveGenType gen = generated;
    BitBoard from_mask = ALL;
    BitBoard to_mask = ALL;
    if (generated == BEST)
    {
        if (!best_move)
            return;
        gen = type(best_move) & CAPTURE ? CAPTURES : QUIETS;
        if (gen > wanted)
            return;
        from_mask = bb(from(best_move));
        to_mask = bb(to(best_move));
    }
    generate_pieces<PAWN>(gen, from_mask, to_mask);
    generate_pieces<KNIGHT>(gen, from_mask, to_mask);
    generate_pieces<BISHOP>(gen, from_mask, to_mask);
    generate_pieces<ROOK>(gen, from_mask, to_mask);
    generate_pieces<QUEEN>(gen, from_mask, to_mask);
    generate_pieces<KING>(gen, from_mask, to_mask);
    std::sort(&moves[index], &moves[count]);
}

Move MoveGen::next()
{
    while (index >= count && generated < wanted)
        generate();
    if (index >= count)
        return NULL_MOVE;
    return moves[index++].move;
}

int evaluate()
{
    return 15 + position.piece_square_values[position.next] - position.piece_square_values[~position.next];
}

enum HashFlags : std::uint8_t { GEN_MASK = 0x3f, LOWER = 0x40, UPPER = 0x80 };

inline HashFlags& operator|=(HashFlags& lhs, HashFlags rhs) { return lhs = static_cast<HashFlags>(lhs | rhs); }

struct alignas(8) HashEntry
{
    std::uint16_t key;
    std::int16_t value;
    Move best_move;
    std::int8_t depth;
    HashFlags flags;

    int generation() const { return flags & GEN_MASK; }
    int get_value(int ply) const
    {
        int hv = value;
        if (hv > 32000)
            hv -= ply;
        else if (hv < -32000)
            hv += ply;
        return hv;
    }
};

static HashEntry* hash_table;
static std::size_t hash_size;
static int hash_generation;

std::size_t hash_index(const Position& position)
{
    return ((position.hash() & 0xffffffffULL) * hash_size) >> 32;
}

int hash_score(int depth, HashFlags flags)
{
    if ((flags & (LOWER | UPPER)) == (LOWER | UPPER))
        depth += 3;
    return depth;
}

void save_hash(int value, int ply, int depth, Move mv, int alpha, int beta)
{
    HashFlags flags = static_cast<HashFlags>(hash_generation & GEN_MASK);
    if (value > alpha)
        flags |= LOWER;
    if (value < beta)
        flags |= UPPER;
    if (value > 32000)
        value += ply;
    else if (value < -32000)
        value -= ply;
    HashEntry& e = hash_table[hash_index(position)];
    std::uint16_t key = static_cast<std::uint16_t>(position.hash() >> 48);
    if (hash_score(e.depth, e.flags) <= hash_score(depth, flags) || (e.key != key && e.generation() != hash_generation))
        e = HashEntry{key, static_cast<std::int16_t>(value), mv, static_cast<std::int8_t>(depth), flags};
}

HashEntry* load_hash()
{
    HashEntry* e = &hash_table[hash_index(position)];
    if (e->key != static_cast<uint16_t>(position.hash() >> 48) ||
            (e->best_move && !(position.color_bb[position.next] & from(e->best_move))))
        return nullptr;
    return e;
}

struct PvLine
{
    int length;
    Move moves[128];
};

static PvLine pv_lines[128] alignas(64);

void update_pv(Move best_move, int ply, bool end)
{
    pv_lines[ply].moves[0] = best_move;
    if (end)
    {
        pv_lines[ply].length = 1;
    }
    else
    {
        int len = pv_lines[ply + 1].length;
        std::copy(&pv_lines[ply + 1].moves[0], &pv_lines[ply + 1].moves[len], &pv_lines[ply].moves[1]);
        pv_lines[ply].length = 1 + len;
    }
}

struct Search
{
    std::istream& in;
    std::ostream& out;
    std::clock_t total_time;
    std::clock_t increment;
    std::clock_t movetime;
    int moves_to_go;
    std::clock_t max_time;
    std::clock_t start;
    long long nodes;
    int sel_depth;
    bool stopped;
    Stack* stack;

    Search(std::istream& i, std::ostream& o, std::clock_t time, std::clock_t inc, std::clock_t movetime, int moves_to_go, Stack* stack);

    bool is_stopped();
    bool check_stop_command();
    bool check_time(int changes, int improving);

    int qsearch(int ply, int depth, int alpha, int beta);
    std::pair<int, Move> search(bool pv, int ply, int depth, int alpha, int beta);
    void iterate(int max_depth);

    Memo do_move(int ply, Move mv)
    {
        Memo memo = position.do_move(mv);
        stack[ply + 1].prev_move = mv;
        stack[ply + 1].key = position.hash();
        return memo;
    }

    void undo_move(Move mv, const Memo& memo) { position.undo_move(mv, memo); }
};

Search::Search(std::istream& i, std::ostream& o, std::clock_t time, std::clock_t inc, std::clock_t mt, int mtg, Stack* st)
    : in{i}, out{o}, total_time{time}, increment{inc}, movetime{mt}, moves_to_go{mtg}, max_time{mt},
    start{std::clock()}, nodes{}, sel_depth{}, stopped{}, stack{st}
{
    if (total_time != static_cast<std::clock_t>(-1))
    {
        total_time -= std::min<std::clock_t>(total_time / 8, CLOCKS_PER_SEC / 4);
        movetime = max_time = std::min(movetime, total_time);
    }
}

bool Search::is_stopped()
{
    if (!stopped && (nodes & 0xff) == 0)
    {
        if (std::clock() - start > max_time)
            stopped = true;
        else if ((nodes & 0x3ffff) == 0)
        {
            if (check_stop_command())
                stopped = true;
        }
    }
    return stopped;
}

bool Search::check_stop_command()
{
    if (in.rdbuf()->in_avail())
    {
        std::string line;
        std::getline(in, line);
        std::istringstream parser{line};
        std::string token;
        parser >> token;
        if (token == "stop")
            return true;
        else if (token == "isready")
            out << "readyok" << std::endl;
    }
    return false;
}

bool Search::check_time(int changes, int improving)
{
    if (total_time != static_cast<std::clock_t>(-1) && !stopped)
    {
        int pieces = popcount(position.color_bb[WHITE] | position.color_bb[BLACK]);
        max_time = std::min(total_time, 26 * total_time / ((4 + ((changes <= 1) * std::max(0, improving - 1))) * (12 + pieces)) + 3 * increment);
        std::clock_t target_time = std::min(
            max_time,
            34 * total_time / ((4 + ((changes <= 1) * std::max(0, improving - 1))) * std::min(32 + 19 * pieces, 11 * moves_to_go))
                    + 16 * increment / (32 + pieces));

        if (std::clock() - start > target_time)
            stopped = true;
    }
    return stopped;
}

int Search::qsearch(int ply, int depth, int alpha, int beta)
{
    assert(ply < 128);
    int orig_alpha = alpha;

    Square king_sq = first_square(position.type_bb[KING] & position.color_bb[position.next]);
    BitBoard checkers = attackers(king_sq, ~position.next);

    int pat = checkers ? -32767 + ply : evaluate();
    if (pat >= beta)
        return beta;
    if (pat > alpha)
        alpha = pat;

    Move best = NULL_MOVE;

    HashEntry* he = load_hash();
    if (he)
    {
        best = he->best_move;
        if (he->depth >= depth && (he->flags & LOWER) && he->get_value(ply) >= beta)
            return beta;
    }

    MoveGen gen{checkers ? QUIETS : CAPTURES, best, stack[ply]};

    while (Move mv = gen.next())
    {
        if (is_stopped())
            return alpha;

        if (!checkers && !(type(mv) & PROMOTION) && pat + material[type(position.squares[to(mv)])] < alpha - 50)
            continue;

        if (!checkers && !(type(mv) & PROMOTION) && mv != best && depth < -1 &&
                (pawn_attack[position.next][to(mv)] & position.type_bb[PAWN] & position.color_bb[~position.next]) &&
                material[type(position.squares[from(mv)])] > material[type(position.squares[to(mv)])] + 150)
            continue;

        ++nodes;
        Memo memo = do_move(ply, mv);
        int v;
        if (attackers(from(mv) == king_sq ? to(mv) : king_sq, position.next))
            v = -32767;
        else
            v = -qsearch(ply + 1, std::max(-2, depth - 1), -beta, -alpha);
        undo_move(mv, memo);

        if (v > alpha)
        {
            alpha = v;
            best = mv;
        }
        if (alpha >= beta)
            break;
    }

    if (best)
        save_hash(alpha, ply, 0, best, orig_alpha, beta);
    return alpha;
}

std::pair<int, Move> Search::search(bool pv, int ply, int depth, int alpha, int beta)
{
    Move prev_best = NULL_MOVE;
    HashEntry* he = load_hash();
    int hv;
    if (he)
    {
        hv = he->get_value(ply);
        if ((!pv || ply > 0) && he->depth >= depth + pv)
        {
            if (hv >= beta && (he->flags & LOWER))
                return {beta, he->best_move};
            if (hv <= alpha && (he->flags & UPPER))
                return {alpha, he->best_move};
        }
        prev_best = he->best_move;
    }

    Square king_sq = first_square(position.type_bb[KING] & position.color_bb[position.next]);
    BitBoard checkers = attackers(king_sq, ~position.next);
    int eval = evaluate();
    if (he && ((hv > eval && (he->flags & LOWER)) || (hv < eval && (he->flags & UPPER))))
        eval = hv;

    if (!pv && !checkers && depth <= 3 && eval > beta + 240 * depth - 140)
        return {beta, NULL_MOVE};

    if (ply >= sel_depth)
        sel_depth = ply + 1;

    if (!pv &&
            ply > 1 &&
            stack[ply].prev_move != NULL_MOVE &&
            depth >= 4 &&
            eval > beta + 50 &&
            !checkers &&
            alpha > -32000 &&
            popcount(position.color_bb[position.next] & ~position.type_bb[PAWN]) > 1)
    {
        Memo memo = do_move(ply, NULL_MOVE);

        int v = -search(false, ply + 1, depth - 2 - (eval - beta) / 200, -beta, -beta + 1).first;
        undo_move(NULL_MOVE, memo);
        if (v >= beta)
            return {beta, NULL_MOVE};
    }

    MoveGen gen{QUIETS, prev_best, stack[ply]};
    Move best = NULL_MOVE;
    int orig_alpha = alpha;

    int move_count = 0;
    int extension = 0;
    if (checkers)
        extension++;

    while (Move mv = gen.next())
    {
        if (!checkers && move_count && depth <= 5 && eval < alpha - (depth * 240 - 140) && !(type(mv) & (CAPTURE | PROMOTION)))
            continue;

        int new_depth = depth + extension - 1;

        int reduction = 0;
        if (new_depth >= 3 && move_count && !checkers && !(type(mv) & (CAPTURE | PROMOTION)) &&
                mv != prev_best && mv != stack[ply].killer_moves[0] && mv != stack[ply].killer_moves[1])
            reduction = std::clamp(move_count / 4 + (he && !(he->flags & LOWER)), 0, depth / 3);

        ++nodes;
        ++move_count;

        Memo memo = do_move(ply, mv);

        int v = beta;
        if (attackers(from(mv) == king_sq ? to(mv) : king_sq, position.next))
        {
            v = -32767;
            gen.moves[gen.index - 1].move = NULL_MOVE;
            --move_count;
        }
        else if (repetition(&stack[ply + 1]))
        {
            v = 0;
        }
        else if (new_depth <= 0 && !checkers)
        {
            v = -qsearch(ply + 1, 0, -beta, -alpha);
        }
        else
        {
            if (!pv || alpha > orig_alpha)
            {
                v = -search(false, ply + 1, new_depth - reduction, -alpha - 1, -alpha).first;
                if (v > alpha && reduction)
                    v = -search(false, ply + 1, new_depth, -alpha - 1, -alpha).first;
            }
            if (v > alpha && alpha < beta - 1)
                v = -search(pv, ply + 1, new_depth, -beta, -alpha).first;
        }

        undo_move(mv, memo);

        if (v > alpha)
        {
            alpha = v;
            best = mv;
        }
        if (is_stopped())
            return {alpha, best};
        if (alpha >= beta)
        {
            alpha = beta;
            break;
        }
    }

    if (move_count == 0)
    {
        if (pv)
            pv_lines[ply].length = 0;
        return {checkers ? -32767 + ply : 0, NULL_MOVE};
    }

    assert(alpha > -32767);
    if (alpha >= beta)
    {
        if (!(type(best) & CAPTURE))
            stack[ply].save_killer(best);
        if (depth > 1)
        {
            int inc = 450 + 36 * depth;
            MoveHistory* hist = history[position.next];
            for (int i = gen.index - 1; i >= 0; --i)
            {
                Move m = gen.moves[i].move;
                if (!m)
                    continue;
                bool cut = (m == best);
                if (type(m) & CAPTURE)
                    capture_history[6 * type(position.squares[to(m)]) + type(position.squares[from(m)])][to(m)].hit(inc, cut);
                else
                    hist[m & FROM_TO_MASK].hit(inc, cut);
            }
        }
    }
    save_hash(alpha, ply, depth, best ? best : prev_best, orig_alpha, beta);

    if (pv && alpha > orig_alpha && alpha < beta)
        update_pv(best, ply, depth <= 1);
    return {alpha, best};
}

void Search::iterate(int max_depth)
{
    std::pair<int, Move> best{};
    int changes = 0;
    int improving = 0;
    int last_change = 0;

    for (int depth = 1; depth <= max_depth; ++depth)
    {
        sel_depth = 0;

        auto v = search(true, 0, depth, -32767, 32767);
        if (!stopped || !best.second)
        {
            if (v.second != best.second)
            {
                changes++;
                last_change = depth;
            }
            if (v.first > best.first)
                improving++;
            else if (v.first < best.first)
                improving = 0;
            best = v;
        }

        if (changes > 0 && depth - last_change >= 3)
            changes--;

        assert(best.second != NULL_MOVE);
        std::clock_t now = std::clock();
        out << "info depth " << depth << " seldepth " << sel_depth << " score ";
        if (best.first > 32000)
            out << "mate " << ((32767 - best.first + 1) / 2);
        else if (best.first < -32000)
            out << "mate " << ((-32767 - best.first) / 2);
        else
            out << "cp " << best.first;
        out << " nodes " << nodes
            << std::fixed << std::setprecision(0) << " time " << (static_cast<double>(now - start) * 1000. / CLOCKS_PER_SEC)
            << " nps " << (nodes * CLOCKS_PER_SEC / static_cast<double>(now - start)) << " pv";
        for (int i = 0; i < pv_lines[0].length; i++)
            out << ' ' << pv_lines[0].moves[i];
        out << std::endl;

        if (check_time(changes, improving))
            break;
    }
    out << "bestmove " << best.second << std::endl;
}

#ifdef TUNE
std::vector<std::pair<Position, int>> tuning_positions;

double evaluation_error()
{
    double error = 0.;
    for (auto& pos : tuning_positions)
    {
        position.reset();
        position.next = pos.first.next;
        position.halfmove_clock = pos.first.halfmove_clock;
        for (Square sq = A1; sq <= H8; sq++)
        {
            if (pos.first.squares[sq])
                position.set(sq, pos.first.squares[sq]);
        }

        error += std::pow(pos.second * 0.5 - 1. / (1. + std::pow(0.99536, evaluate())), 2);
    }
    return error / tuning_positions.size();
}

void find_best_value(std::pair<int*, double>& variable, double& best_error, int start_delta)
{
    double start_error = best_error;
    for (int delta = start_delta; delta > 0; delta /= 2)
    {
        for (int sd : {-delta, delta})
        {
            int prev_value = *variable.first;
            *variable.first += sd;
            double error = evaluation_error();
            if (error >= best_error)
                *variable.first = prev_value;
            else
            {
                best_error = error;
                break;
            }
        }
    }
    variable.second = start_error - best_error;
    std::cout << std::fixed << std::setprecision(4) << (10000. * best_error) << std::endl;
}
#endif

constexpr char startfen[] = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

int main()
{
    std::ios::sync_with_stdio(false);
    std::string line;

#ifdef TUNE
    int pos_count = 0;
    while (getline(std::cin, line))
    {
        ++pos_count;
        std::istringstream parser{line};
        position.parse(parser);
        int score, result;
        parser.ignore();
        parser >> score;
        parser.ignore();
        parser >> result;

        if (popcount(position.type_bb[WHITE] | position.type_bb[BLACK]) <= -32 + (pos_count % 64))
            continue;
        if (position.halfmove_clock >= 25 + (pos_count % 50))
            continue;
        tuning_positions.push_back({position, result});
    }

    double best_error = evaluation_error();
    std::cout << std::fixed << std::setprecision(4) << (10000. * best_error) << std::endl;

    std::vector<std::pair<int*, double>> variables;
    for (int i = 1; i < 5; i++)
        variables.push_back({&material[i], 0});
    for (auto& table : piece_square_table)
    {
        for (int& v : table)
            variables.push_back({&v, 0});
    }

    for (int k = 0; k < 12; k++)
    {
        for (auto& p : variables)
            find_best_value(p, best_error, 1);
        for (int n = 0; n < 4; n++)
        {
            std::cout << "===== " << n << " =====" << std::endl;

            std::sort(
                variables.begin(), variables.end(),
                [](const std::pair<int*, double>& lhs, const std::pair<int*, double>& rhs) { return lhs.second > rhs.second; }
            );

            double cutoff = variables.front().second * std::pow(2., -n - 1.);
            for (auto& v : variables)
            {
                if (v.second < cutoff)
                    break;
                find_best_value(v, best_error, 32 / (n + k + 1));
            }
        }
    }

    std::cout << std::fixed << std::setprecision(4) << (10000. * best_error) << std::endl;
    std::cout << "int material[6] = {";
    for (int i = 0; i < 6; i++)
    {
        if (i > 0)
            std::cout << ", ";
        std::cout << material[i];
    }
    std::cout << "};" << std::endl;
    std::cout << "int piece_square_table[6][64] =\n";
    std::cout << "{\n";
    for (int i = 0; i < 6; i++)
    {
        std::cout << "    {";
        for (int j = 0; j < 64; j++)
        {
            if (j % 8 == 0)
                std::cout << "\n        ";
            std::cout << piece_square_table[i][j] << ", ";
        }
        std::cout << "\n    },\n";
    }
    std::cout << "};" << std::endl;
    return 0;
#endif

    std::size_t hash_mb = 1;
    bool debug = false;
    Stack stack[256] = {};

    while (getline(std::cin, line))
    {
        std::istringstream parser{line};
        std::string token;
        parser >> token;

        if (token == "uci")
        {
            std::cout
                << "id name seawall " STRINGIFY(SEAWALL_VERSION) << "\n"
                << "id author petur\n"
                << "option name Hash type spin default 1 min 1 max 65536\n"
                << "uciok" << std::endl;
        }
        else if (token == "debug")
        {
            parser >> token;
            if (token == "on")
                debug = true;
            else if (token == "off")
                debug = false;
        }
        else if (token == "setoption")
        {
            parser >> token;
            parser >> token;
            for (char& c : token)
                c = std::tolower(static_cast<unsigned char>(c));
            if (token == "hash")
            {
                parser >> token;
                parser >> hash_mb;
            }
        }
        else if (token == "isready")
        {
            if (!king_attack[A1])
                init_bitboards();
            std::size_t new_hash_size = (hash_mb << 20) / sizeof(HashEntry);
            if (new_hash_size != hash_size)
            {
                delete[] hash_table;
                hash_size = new_hash_size;
                hash_table = new HashEntry[hash_size];
                std::fill_n(hash_table, hash_size, HashEntry{});
            }
            std::cout << "readyok" << std::endl;
        }
        else if (token == "ucinewgame")
        {
            if (hash_table)
                std::fill_n(hash_table, hash_size, HashEntry{});
        }
        else if (token == "position")
        {
            for (Color c : {WHITE, BLACK})
                std::fill_n(history[c], FROM_TO_SIZE, MoveHistory{});
            for (int c = PAWN; c < KING; c++)
                for (int m = PAWN; m <= KING; m++)
                    std::fill_n(capture_history[6 * c + m], 64, MoveHistory{static_cast<std::int16_t>(384 - m)});
            parser >> token;
            if (token == "startpos")
            {
                std::istringstream start{startfen};
                position.parse(start);
            }
            else
                position.parse(parser);
            std::fill_n(stack, position.halfmove_clock, Stack{});
            stack[position.halfmove_clock].key = position.hash();

            parser >> token;
            while (parser >> token)
            {
                Move mv = position.parse_move(token);
                position.do_move(mv);
                stack[position.halfmove_clock].prev_move = mv;
                stack[position.halfmove_clock].key = position.hash();
            }
            if (debug)
                position.debug(std::cout);
        }
        else if (token == "go")
        {
            int max_depth = 128;
            std::clock_t time = -1;
            std::clock_t inc = 0;
            std::clock_t movetime = std::numeric_limits<std::clock_t>::max();
            int moves_to_go = 10000;

            while (parser >> token)
            {
                if (token == "depth")
                    parser >> max_depth;
                if (token == (position.next == WHITE ? "wtime" : "btime"))
                {
                    long millis;
                    parser >> millis;
                    time = millis * CLOCKS_PER_SEC / 1000L;
                }
                if (token == (position.next == WHITE ? "winc" : "binc"))
                {
                    long millis;
                    parser >> millis;
                    inc = millis * CLOCKS_PER_SEC / 1000L;
                }
                if (token == "movetime")
                {
                    long millis;
                    parser >> millis;
                    movetime = millis * CLOCKS_PER_SEC / 1000L;
                }
                if (token == "movestogo")
                    parser >> moves_to_go;
            }

            ++hash_generation;
            Search{std::cin, std::cout, time, inc, movetime, moves_to_go, &stack[position.halfmove_clock]}.iterate(max_depth);
        }
        else if (token == "quit")
        {
            break;
        }
    }

    return 0;
}
