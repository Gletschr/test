#include "Utils.h"

#include <QFile>
#include <QList>
#include <QTransform>
#include <QByteArray>

Utils::Utils() {

}

Utils::~Utils() {

}

void Utils::scaleContour(const QVector<QPointF> &contour, float scale, QVector<QPointF> &scaledContour) {
	Q_ASSERT((&contour) != (&scaledContour));
	QPointF refPoint = Utils::computeContourCentroid(contour);
	Utils::scaleContour(contour, refPoint, scale, scaledContour);
}

void Utils::scaleContour(const QVector<QPointF> &contour, const QPointF &refPoint, float scale, QVector<QPointF> &scaledContour) {
	Q_ASSERT((&contour) != (&scaledContour));
	QTransform transform;
	transform.translate(refPoint.x(), refPoint.y());
	transform.scale(scale, scale);
	transform.translate(-refPoint.x(), -refPoint.y());
	scaledContour = transform.map(contour);
}

void Utils::rotateContour(const QVector<QPointF> &contour, const QPointF &refPoint, float angle, QVector<QPointF> &rotatedContour) {
	Q_ASSERT((&contour) != (&rotatedContour));
	QTransform transform;
	transform.translate(refPoint.x(), refPoint.y());
	transform.rotate(angle);
	transform.translate(-refPoint.x(), -refPoint.y());
	rotatedContour = transform.map(contour);
}

//
// en.wikipedia.org/wiki/Centroid#Centroid_of_a_polygon
//
QPointF Utils::computeContourCentroid(const QVector<QPointF> &contour) {
	Q_ASSERT(contour.count() >= 2);
	QPointF centroid;
	qreal signedArea = 0.0f;
	const auto computeStep = [&centroid, &signedArea](const QPointF &p0, const QPointF &p1) {
		qreal s = p0.x() * p1.y() - p1.x() * p0.y();
		centroid.setX(centroid.x() + (p0.x() + p1.x()) * s);
		centroid.setY(centroid.y() + (p0.y() + p1.y()) * s);
		signedArea += s;
	};
	int pointsCountMinusOne = contour.count() - 1;
	for (int i = 0; i < pointsCountMinusOne; ++ i) {
		computeStep(contour[i], contour[i + 1]);
	}
	computeStep(contour[pointsCountMinusOne], contour[0]);
	signedArea *= 0.5f;
	qreal s = 6.0f * signedArea;
	centroid.setX(centroid.x() / s);
	centroid.setY(centroid.y() / s);
	return centroid;
}

bool Utils::loadPointsFromFile(const QString &fileName, QVector<QPointF> &output) {
	QFile file(fileName);
	if (!file.open(QFile::ReadOnly)) {
		return false; // Unable to read file.
	}
	QByteArray contents = file.readAll();
	file.close();
	QList<QByteArray> splitted = contents.split(';');
	int splittedCount = splitted.count();
	if (splittedCount % 2 || splittedCount == 0) {
		return false; // Odd or zero coordinates count.
	}
	output.resize(splittedCount / 2);
	bool result = true;
	bool parsedSuccesfully = true;
	for (int i = 0; i < splittedCount; i += 2) {
		QPointF &point = output[i / 2];
		point.setX(splitted[i].toFloat(&parsedSuccesfully));
		result &= parsedSuccesfully;
		point.setY(splitted[i + 1].toFloat(&parsedSuccesfully));
		result &= parsedSuccesfully;
	}
	return result;
}
