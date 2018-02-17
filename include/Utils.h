#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include <QPointF>
#include <QVector>

///
/// \brief The Utils class.
///
class Utils {

	///
	Utils();

	///
	~Utils();

public:

	///
	/// \brief Load points from file.
	/// \param fileName - File name.
	/// \param output - Points array (output value).
	/// \return True on loaded succesfully, false - otherwise.
	///
	static bool loadPointsFromFile(const QString &fileName, QVector<QPointF> &output);

	///
	/// \brief Compute centroid of contour.
	/// \param contour - Contour points array.
	/// \return Centroid point.
	///
	static QPointF computeContourCentroid(const QVector<QPointF> &contour);

	///
	/// \brief Scale contour by its centroid.
	/// \param contour - Contour points array.
	/// \param scale - Scale coefficient.
	/// \param scaledContour - Scaled contour points array (output value).
	///
	static void scaleContour(const QVector<QPointF> &contour, float scale, QVector<QPointF> &scaledContour);

	///
	/// \brief Scale contour around reference point.
	/// \param contour - Contour points array.
	/// \param refPoint - Reference point.
	/// \param scale - Scale coefficient.
	/// \param scaledContour - Scaled contour points array (output value).
	///
	static void scaleContour(const QVector<QPointF> &contour,  const QPointF &refPoint, float scale, QVector<QPointF> &scaledContour);

	///
	/// \brief Rotate contour around reference point by given angle.
	/// \param contour - Contour points array.
	/// \param refPoint - Reference point.
	/// \param angle - Angle to rotate.
	/// \param rotatedPoints - Rotated contour points array (output value).
	///
	static void rotateContour(const QVector<QPointF> &contour, const QPointF &refPoint, float angle, QVector<QPointF> &rotatedContour);

};

#endif // UTILS_H
