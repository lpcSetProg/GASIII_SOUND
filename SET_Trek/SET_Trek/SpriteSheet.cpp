/*
* Filename:         SpriteSheet.cpp
* Project:          PROG2215 - G.A.S. - Assignment - 02 - SET Trek II
* Programmer:       Lev Cocarell
* Date:             2017-13-03
* Description: 

* This source file contains the SpriteSheet class that originally was sourced
* from the "Whats a Creel" Direct2D tutorial and the example supplied in GAS
* class. It has been modified and appended with extra methods to fit the requirements 
* in assingment 2. As well, this class borrows from Kitty's Code Blog on how to implement 
* Direct2D graphic objects.

* NOTE: Description comments from GAS class example.
* "The concept of this class is that it will be passed
* a filename and graphics object/rendertarget, then, will
* proceed to create the needed WIC components to read,
* decode, and then encode the bitmap file from disk into
* a compatible D2D bitmap."  Source: GAS class example comments.
*/


#include "SpriteSheet.h"



//=============================================================================
// SpriteSheet Methods
//=============================================================================


/*
* Method:
* Description:
* "This method was originally from the "What's a Kreel" tutorial and the 
* the example file provided in class. "We need this approach to be able to 
* address pretty much any bitmap from disk/resources into the game and use it
* within Directx (D2D specifically for now)." Source: GAS class example comments.
* Parameters: wchar_t* filename, Graphics* gfx
* Returns: N/A
*/
SpriteSheet::SpriteSheet(wchar_t* filename, Graphics* gfx)
{
	this->gfx = gfx; //save the gfx parameter for later
	bmp = NULL; //This needs to be NULL to start off
	HRESULT hr;

	//Step 1: Create a WIC Factory
	IWICImagingFactory *wicFactory = NULL;
	hr = CoCreateInstance(
		CLSID_WICImagingFactory, //CLS ID of the object about to be made
		NULL, //not needed here, but just denotes this isn't part of an aggregate
		CLSCTX_INPROC_SERVER, //Indicates this DLL runs in the same process
		IID_IWICImagingFactory, //Reference to an Interface that talks to the object
		(LPVOID*)&wicFactory); //This is our pointer to the WICFactory, once set up.

//Step 2: Create a Decoder to read file into a WIC Bitmap
	IWICBitmapDecoder *wicDecoder = NULL;
	hr = wicFactory->CreateDecoderFromFilename(
		filename, //The filename we passed in already
		NULL, //This can be used to indicate other/preferred decoders. Not something we need.
		GENERIC_READ, //indicates we're reading from the file, vs writing, etc.
		WICDecodeMetadataCacheOnLoad, //Needed, but would only help if we were keeping this in WIC
		&wicDecoder); //Our pointer to the Decoder we've setup

//Step 3: Read a 'frame'. We're really just moving the whole image into a frame here
	IWICBitmapFrameDecode* wicFrame = NULL;
	hr = wicDecoder->GetFrame(0, &wicFrame); //0 here means the first frame... or only one in our case
	//Now, we've got a WICBitmap... we want it to be a D2D bitmap

//Step 4: Create a WIC Converter
	IWICFormatConverter *wicConverter = NULL;
	hr = wicFactory->CreateFormatConverter(&wicConverter);

	//Step 5: Configure the Converter
	hr = wicConverter->Initialize(
		wicFrame, //Our frame from above
		GUID_WICPixelFormat32bppPBGRA, //Pixelformat
		WICBitmapDitherTypeNone, //not important for us here
		NULL, //indicates no palette is needed, not important here
		0.0, //Alpha Transparency, can look at this later
		WICBitmapPaletteTypeCustom //Not important for us here
	);

	//Step 6: Create the D2D Bitmap! Finally!
	gfx->GetRenderTarget()->CreateBitmapFromWicBitmap(
		wicConverter, //Our friend the converter
		NULL, //Can specify D2D1_Bitmap_Properties here, not needed now
		&bmp //Our destination bmp we specified earlier in the header
	);

	//Let us do some private object cleanup!
	if (wicFactory) wicFactory->Release();
	if (wicDecoder) wicDecoder->Release();
	if (wicConverter) wicConverter->Release();
	if (wicFrame) wicFrame->Release();
}


/*
* Method: SpriteSheet
* Description:
* This method was originally from the "What's a Kreel" tutorial and the 
* the example file provided in class.
* Parameters: N/A
* Returns: N/A
*
*/
SpriteSheet::SpriteSheet(wchar_t* filename, Graphics* gfx, int sprite_width, int sprite_height) :
	SpriteSheet(filename, gfx)
{
	this->sprite_height = sprite_height;  //uniform w + h  for sprite sheet 
	this->sprite_width = sprite_width;

}


/*
* Desctructor:
* This destructor releases all the bmps used in the game.
*/
SpriteSheet::~SpriteSheet()
{
	if (bmp) bmp->Release();
}


//NOTE: All methods below are written by programmer for 
//GAS Assignment 1 and 2. Unless otherwise stated.
//

//=============================================================================
// Apply ChromaKey 
//=============================================================================
/*
* Method: Add_Chromakey
* Description:
* This method applies the Direct2d effect "ChromaKey" to all bitmaps used 
* in SectorMap1. First it creates the effect from a render target, then it 
* sets the values for the effect. It is modular because not all bitmaps used 
* the standard "green value" (i.e the enemy ship has a blue background). 
* This chromakey effect is intended to render all the images "transparent" during 
* the game, eliminating the blue or green background surrounding the original bitmap.
*
* Parameters: float r, float g, float b, float input, float tolerance
* Returns: N/A
*
*/
void SpriteSheet::Add_Chromakey(float r, float g, float b, float input, float tolerance)
{
	gfx->GetRenderTarget()->CreateEffect(CLSID_D2D1ChromaKey, &chromakeyEffect);

	chromakeyEffect->SetInput(input, bmp);
	chromakeyEffect->SetValue(D2D1_CHROMAKEY_PROP_COLOR, D2D1::Vector3F(r, g, b));
	chromakeyEffect->SetValue(D2D1_CHROMAKEY_PROP_TOLERANCE, tolerance);
	chromakeyEffect->SetValue(D2D1_CHROMAKEY_PROP_INVERT_ALPHA, false);
	chromakeyEffect->SetValue(D2D1_CHROMAKEY_PROP_FEATHER, false);
}



//=============================================================================
// Draw Methods for SectorMap1
//=============================================================================

/*
* Method: Draw
* Description: 
* This method is a variation on the original Draw method used in assignment 1. 
* It is more modular 
* Parameters: float x, float y, float c , float d, float angle
* Returns: N/A
*
*/
void SpriteSheet::Draw(float x, float y, float c , float d, float angle)
{
	D2D_POINT_2F vector;
	vector = { x, y };

	int w = bmp->GetSize().width;
	int h = bmp->GetSize().height;


	gfx->GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Rotation(angle, D2D1::Point2F((x + h /2) , (y + w /2) )));
	
	gfx->GetRenderTarget()->DrawImage(chromakeyEffect, vector);
		
}


/*
* Method: DrawBackground
* Description: General static 'draw', intended for use with standard background image of sector map.
//* Based off examples from class and the tutorial from 'What's a Creel'. 
* Parameters: N/A
* Returns: N/A
*
*/
void SpriteSheet::DrawBackground()
{
	gfx->GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Rotation(0, D2D1::Point2F(0, 0)));

	gfx->GetRenderTarget()->DrawBitmap(
		bmp, //Bitmap we built from WIC
		D2D1::RectF(0.0f, 0.0f,
			bmp->GetSize().width, bmp->GetSize().height), //Destination rectangle
		1.0f, //Opacity or Alpha
		D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
		//Above - the interpolation mode to use if this object is 'stretched' or 'shrunk'. 
		D2D1::RectF(0.0f, 0.0f, bmp->GetSize().width, bmp->GetSize().height) //Source Rectangle

	);
}

