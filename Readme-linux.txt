Building BodySlide (BS) and Outfit Studio (OS) on Linux

The only file that you have to worry about is CmakeLists.txt.
It specifies the build process and tells the compiler (or linker to be more
precise), what libraries to include and where they are on your system, if they
are not in the standard lib directories.

IMPORTANT!!!
The dialogue window opening on first launch to tell OS or BS where to find your
game is bugged, and may not work.
Please run Windows BodySlide at least once on wine to populate the Config.xml
file. Then open Config.xml and change the windows paths you see to use the
actual absolute (no ./ ; begin from root) linux path.
My personal config as example:

    <GameDataPaths>
        <Fallout3></Fallout3>
        <FalloutNewVegas></FalloutNewVegas>
        <Skyrim></Skyrim>
        <Fallout4></Fallout4>
        <SkyrimSpecialEdition>/run/media/michael/Skyrim/Bottles/TESV/drive_c/GOG Games/Skyrim Anniversary Edition/data/</SkyrimSpecialEdition>
        <Fallout4VR></Fallout4VR>
        <SkyrimVR></SkyrimVR>
    </GameDataPaths>
    <GameDataPath>/run/media/michael/Skyrim/Bottles/TESV/drive_c/GOG Games/Skyrim Anniversary Edition/data/</GameDataPath>

In the upper part, you specify the path for the game, you have installed BS for.
The second part is the same, as it is the currently used default path
that gets chosen, when you open up Bodyslide or OutfitStudio.

With that out of the way, let’s get to the actual build procedure.

Requirements:

  -BS&OS repo:	You will obviously need this repository.
			Use git clone in your terminal to clone the repo to a
			directory of your choosing.

  -wxWidgets:	To install wxWidgets, first look for it in your distribution
			packages. It will be named something like:
			wxWidgets-devel, wxWidgets-[VERSION]-devel, wxWdigets-dev,
			etc.
			There is a possibility, that the system provided packages
			won’t work. If your get an ABI mismatch error, which is caused
			by wxWidgets having been compiled with a different compiler
			version, than the compiler you are using for BS and OS, you
			will have to compile it yourself. Check out the wxWidgets docs
			here:
			[https://wiki.wxwidgets.org/Compiling_and_getting_started]
			On Linux, wxWidgets use GTK as its base by default. There is a
			QT version, if you want, but be warned, that it is not up to
			par with the GTK version and has some major issues, so my
			advice is to stick to GTK.
			With GTK, you have two options if you compile it yourself,
			which are GTK2 and GTK3 respectively. Both are not perfect,
			but they have (probably) full functionality (at least what I
			have tested	or patched), just with some graphic weirdness.
			Please be advised though, that on GTK3, there seems to be
			issues with	barely to not visible control elements, such as
			the Group selector in Bodyslide on my system, which is why I
			would advice to use GTK2. If you have problems with barely
			visible text or icons, you will have to try different GTK
			themes, to see what is the most usable. As I use KDE, i do not
			know, if that is a feasible strategy on Gnome or other GTK
			based DEs. (I personally use WhiteSur-Dark-nord) as it gets me
			the best looking and most usable UI, that somewhat fits my
			system Theme.


  -DirectX:		I know, weird, but you will need DirectX-Headers.
			You can install them from your system packages, named
 			something like:
			DirectX-Headers, directx-headers, etc.
			Sadly it is not included in many Distros, so you will probably
			have to compile from the Microsoft Github site here:
			[https://github.com/microsoft/DirectX-Headers].
			You can, alternatively, just copy the headers provided in the
			repo.
			You will have to specify in CmakeLists.txt
			where to find the headers. For that, you have to edit this
			line:

			if(LINUX)
				include_directories(BEFORE /path/of/headers)
			endif()

  -GLEW:		Get the development package of GLEW from your system packages.
			It should be named something like:
			glew-devel / glew-dev / libglew-dev

  -FBX SDK:		The install package of FBX SDK can be found here:
			[https://aps.autodesk.com/developer/overview/fbx-sdk]
			Inside the downloaded Archive, you will find a file called
			Install_FbxSdk.txt, which explains the installation procedure.
			Once you installed FBX SDK, open the CmakeLists.txt and search
			for the line:

			set(fbxsdk_dir /probably/wrong/path)

			now replace the path, with the one of your FBX installation:

			set(fbxsdk_dir /your/install/path)

Build OS and BS:	Now it is Time to build this project. Open the Terminal and
			follow the following steps:

			1. Go to the cloned repository

			   $ cd ./folder with repo/BodySlide-and-Outfit-Studio

			   or right-click the repo in the file explorer and search for
			   something like “open in terminal” in your context menu.
			   I, however, do not know if all File Explorers and DEs
			   support this.

			2. Make a new folder named Release and enter it

			   $ mkdir Release && cd ./Release

			3. Create cmake build configuration from CmakeLists.txt

			   $ cmake -DCMAKE_BUILD_TYPE=Release ..

			4. Build project

			   $ make

			   You can use the flag -j to tell the compiler how many
			   concurrent threads (cores) it is allowed to use e.g.
			   -j 4 for a 4 core processor (or less if you do other stuff,
			   whilst compiling). This speeds up the compiling process
			   tremendously. Now the make command looks something like
			   this:

			   $ make -j 4

			5. Now copy the final binaries OutfitStudio and BodySlide
			   into the standard BodySlide and OutfitStudio installation,
			   under ./Data/CalienteTools/BodySlide/
			   If you want to have those binaries somewhere else, set
			   WX_BODYSLIDE_DATA_DIR and WX_OUTFITSTUDIO_DATA_DIR to the
			   BodySlide mod installation directory. Since the binaries
			   need to use the files inside the res directory, you will
			   have to copy it into the same place as your freshly
			   compiled binaries.

Be advised, that this compiles only the single-threaded version. BatchBuild
Outfits will still be faster then on wine, since wine seams to have problems
with ppl based multi-threading, but sadly not as fast as on Windows. I tried to
use tbb, but it will not work with wxGTK, wxQT(works sporadically, idk why) and
wxX11, which are the three options for wxWidgets on Linux, without major effort.
(take that with an ocean full of salt, as I have no actual idea, what I am
doing, when it comes to multi-threading). Maybe using TBB or BOOST for
multi-threading in the windows build will make it work on Wine, but since I have
no windows machine to compile and test it, I cannot follow up on that thought.
