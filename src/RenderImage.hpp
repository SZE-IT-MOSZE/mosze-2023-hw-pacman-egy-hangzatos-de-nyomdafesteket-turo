#ifndef RENDERIMAGE_H
#define RENDERIMAGE_H

__interface IRenderImage
{
public:
	/// <summary>
	/// Produces a char** for the renderer to display
	/// </summary>
	/// <returns>A char matrix of the image to display</returns>
	char** ProduceImage() = 0;

	bool IsUpdateable() = 0;
};
#endif // !RENDERIMAGE_H
