#ifndef GENERATIONINFO_H
#define GENERATIONINFO_H

/// <summary>
/// Unused. Intended use: specify information how the object should be generated
/// </summary>
__interface IGenerationInfo
{
public:
	/// <summary>
	/// The percentage of this GameObject on the map. If returns zero, GetCount() is called instead.
	/// </summary>
	/// <returns>The percentage of this gameObject on the map</returns>
	float GetPercentage();

	/// <summary>
	/// The count of this GameObject on the map. If GetCount returns 0, this GameObject is not generated.
	/// </summary>
	/// <returns>The count of this GameObject on the map</returns>
	int GetCount();

	/// <summary>
	/// Decides if this should be placed on the map regardless of what is already present.
	/// </summary>
	/// <returns></returns>
	bool ForceOverrideGeneration();

};

#endif // !GENERATIONINFO_H
