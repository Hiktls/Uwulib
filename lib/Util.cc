#include "Util.hh"


unsigned long file_size(const char *filename)
{
    FILE *pFile = fopen(filename, "rb");
    fseek (pFile, 0, SEEK_END);
    unsigned long size = ftell(pFile);
    fclose (pFile);
    return size;
}
Util::Util(string tmp,string run,int compressionLevel){
    TMPPATH = tmp;
    RUNPATH = run;
    compression = compressionLevel;
}

int Util::Compress(string source, string dest){
    FILE* infile = fopen(source.c_str(),"rb");
    gzFile outfile = gzopen(dest.c_str(),"wb");
    if (!infile || !outfile) return -1;
    
    char inbuffer[128];
    int num_read = 0;
    unsigned long total_read = 0;
    while ((num_read = fread(inbuffer, 1, sizeof(inbuffer), infile)) > 0) {
        total_read += num_read;
        gzwrite(outfile, inbuffer, num_read);
    }
    fclose(infile);
    gzclose(outfile);
    printf("Read %ld bytes, Wrote %ld bytes,Compression factor %4.2f%%\n",
        total_read, file_size(dest.c_str()),
        (1.0-file_size(dest.c_str())*1.0/total_read)*100.0);
    return 0;
}

int Util::Decompress(string source, string dest){
    gzFile infile = gzopen(source.c_str(),"rb");
    FILE* outfile = fopen(dest.c_str(),"wb");
    if (!infile || !outfile) return -1;
    
    char buffer[128];
    int num_read = 0;
    while ((num_read = gzread(infile, buffer, sizeof(buffer))) > 0) {
        fwrite(buffer, 1, num_read, outfile);
    }
    fclose(outfile);
    gzclose(infile);
    return 0;
}
SDL_Texture* Util::LoadTEX(string relativePath,SDL_Renderer* &Renderer){
    string path;
    if(compression == 1){
        path = TMPPATH+"\\"+relativePath;
    }
    else {
        path = RUNPATH + "\\" + relativePath;
    }
    SDL_Texture* texture = NULL;
    printf("%saaa\n",path.c_str());

    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf("Failed to load file.\n");
        throw std::runtime_error(SDL_GetError());
    }
    else
    {
        texture = SDL_CreateTextureFromSurface( Renderer, loadedSurface );
        if(texture == NULL )
        {
            printf("Failed to load file.\n");
            throw std::runtime_error(SDL_GetError());
        }
        SDL_FreeSurface( loadedSurface );
    }

    return texture;
}
void Util::Packager(string path){
    SHA256 sha;
    Util util(TMPPATH,RUNPATH,compression);
    std::ofstream hashfile(path+"\\hash.sha256");
    for(const auto &entry : std::filesystem::directory_iterator(path)){
        size_t filenameLastSep = entry.path().string().find_last_of("\\");
        string filename = entry.path().string().substr(filenameLastSep+1,entry.path().string().size()-filenameLastSep);
        fs::path extension = entry.path().extension();
        if(extension.string() != ".sha256" && extension.string() != ".ass"){
            util.Compress(entry.path().string(),entry.path().string().append(".ass"));
            // I failed to load file into memory. I am ashamed of myself.
            // The code I stole is from https://stackoverflow.com/a/22210647
            hashfile << util.GetFileHash(entry.path().string()+".ass") << " " << filename << "\n";
            std::filesystem::remove(entry.path());
        }
        else if(extension.string() != ".sha256" && extension.string() == ".ass"){
            std::ifstream file;
            file.open (entry.path(), std::ios::binary | std::ios::in);

            file.seekg (0, std::ios::end);
            long size = file.tellg();
            file.seekg (0, std::ios::beg);    

            char * buffer = new char[size];
            file.read(buffer,size);
            hashfile << sha((unsigned char*)buffer,size) << " " << filename << "\n";
            delete[] buffer;
        }
    }
    hashfile.close();
}

string Util::GetFileHash(string path){
    SHA256 sha;
    std::ifstream file;
    file.open (path, std::ios::binary | std::ios::in);

    file.seekg (0, std::ios::end);
    long size = file.tellg();
    file.seekg (0, std::ios::beg);    

    char * buffer = new char[size];
    file.read(buffer,size);
    string hash = sha((unsigned char*)buffer,size);
    delete[] buffer;
    return hash;
}