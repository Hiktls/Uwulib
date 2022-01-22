#include <MediaManager.hh>




SDL_Surface* MediaManager::LoadBMP(string relativePath,SDL_Surface* MainSurface){
    string path = RUNPATH + "\\" + relativePath;
    SDL_Surface* optSurface = NULL;
    SDL_Surface* tempSurface = NULL;
    tempSurface = SDL_LoadBMP(path.c_str());
    if(tempSurface == NULL){
        printf("Failed to load file.\n");
        throw std::runtime_error(SDL_GetError());
    }
    else {
        optSurface = SDL_ConvertSurface(tempSurface,MainSurface->format,0);
        if(optSurface == NULL){
            printf("Failed to optimize image, Error:%s\n ",IMG_GetError());
            return tempSurface;
        }
        SDL_FreeSurface(tempSurface);
    }
    return optSurface;
}

SDL_Surface* MediaManager::LoadIMG(string relativePath,SDL_Surface* MainSurface){
    string path;
    if(compressionLevel == 1){
        path = TMPPATH+relativePath;
    }
    else {
        path = RUNPATH + "\\" + relativePath;
    }    
    SDL_Surface* optSurface = NULL;
    SDL_Surface* tempSurface = NULL;
    
    tempSurface = IMG_Load(path.c_str());
    
    if(tempSurface == NULL){
        printf("Failed to load file.\n");
        throw std::runtime_error(SDL_GetError());
    }
    
    else {
        optSurface = SDL_ConvertSurface(tempSurface,MainSurface->format,0);
        if(optSurface == NULL){
            printf("Failed to optimize image, Error:%s\n ",IMG_GetError());
            return tempSurface;
        }
        SDL_FreeSurface(tempSurface);
    }
    return optSurface;
}
SDL_Texture* MediaManager::LoadTEX(string relativePath){
    string path;
    if(compressionLevel == 1){
        path = TMPPATH+"\\"+relativePath;
    }
    else {
        path = RUNPATH + "\\" + relativePath;
    }
    SDL_Texture* texture = NULL;

    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf("Failed to load file.\n");
        throw std::runtime_error(SDL_GetError());
    }
    else
    {
        texture = SDL_CreateTextureFromSurface( RENDERER, loadedSurface );
        if(texture == NULL )
        {
            printf("Failed to load file.\n");
            throw std::runtime_error(SDL_GetError());
        }
        SDL_FreeSurface( loadedSurface );
    }

    return texture;
}


void MediaManager::BlitSurface(SDL_Surface* MainSurface,SDL_Surface* TargetSurface,int x,int y,int h,int w){
    SDL_Rect imgRect;
	imgRect.x = x;
	imgRect.y = y;
	imgRect.w = w;
	imgRect.h = h;
	SDL_BlitScaled(TargetSurface,NULL,MainSurface,&imgRect);
}

MediaManager::MediaManager(SDL_Window* WINDOW,string assetsFolder,int compression){
    char buffer[2048];
    compression = compression;
    _getcwd(buffer,2048);
    RUNPATH.append(buffer);
    string assetsPath = RUNPATH+"\\"+assetsFolder;
    
    if(compression == 1){
        compressionLevel = 1;
        Util util;
        string TMP = getenv("TMP");
        ASSETSNAME = assetsFolder;
        if(!fs::exists(TMP+"\\uwuengine")){
            fs::create_directory(TMP.append("\\uwuengine"));
            fs::create_directory(TMP+"\\"+assetsFolder);
            TMPPATH = TMP;
        }
        else{
            TMPPATH = TMP+"\\uwuengine";
        }
        printf("%s\n",assetsPath.c_str());
        // Get ready hashes
        std::ifstream hashList(TMPPATH+"\\"+assetsFolder+"\\hash.sha256");
        string line;
        std::vector<string> fileHashes,fileNames;
        while (std::getline(hashList,line)){
            int deliLoc = line.find_first_of(' ');
            string hash = line.substr(0,deliLoc);
            string name = line.substr(deliLoc,line.size()-deliLoc);
            printf("name: %s,hash: %s\n",name.c_str(),hash.c_str());
            fileHashes.push_back(hash);
            fileNames.push_back(name);
        }
        for(const auto &entry : fs::directory_iterator(assetsPath)){
            size_t filenameLastSep = entry.path().string().find_last_of("\\");
            string filename = entry.path().string().substr(filenameLastSep+1,entry.path().string().size()-filenameLastSep);
            if(entry.path().extension().string() == ".ass"){
                filename = entry.path().string().substr(filenameLastSep+1,entry.path().string().size()-filenameLastSep-entry.path().extension().string().size());
            }
            
            string filePath = TMPPATH+"\\"+assetsFolder+"\\"+filename;            
            string fileHash = util.GetFileHash(entry.path().string());
            
            if(std::find(fileHashes.begin(), fileHashes.end(),fileHash) != fileHashes.end()){
                printf("found\n");
                continue;
                printf("lmao\n");
            }
            else {
                util.Decompress(entry.path().string(),filePath);
            }
        }
    }

    RENDERER = SDL_CreateRenderer( WINDOW, -1, SDL_RENDERER_ACCELERATED );
    if( RENDERER == NULL )
    {
        printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
    }
    if((!IMG_Init(IMG_INIT_PNG)) & IMG_INIT_JPG){
        printf("Failed to init SDL_Image with IMG_INIT_JPG flag. IMG_GetError(): %s\n",IMG_GetError());
    }
}

MediaManager::~MediaManager(){
    printf("%s",TMPPATH.c_str());
    IMG_Quit();
    SDL_DestroyRenderer(RENDERER);
    if(compressionLevel == 1){
    }
}
