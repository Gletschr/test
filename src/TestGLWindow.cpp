#include "TestGLWindow.h"
#include "Utils.h"

TestGLWindow::TestGLWindow() : QOpenGLWindow() {

}

TestGLWindow::~TestGLWindow() {

}

void TestGLWindow::loadAndPrepareRenderResources() {

	QVector<QPointF> points;

	// Load points from file.
	bool isLoaded = Utils::loadPointsFromFile(":/data/dataset.csv", points);

	Q_ASSERT(isLoaded == true);
	Q_ASSERT(points.count() == 68); // Validate input data.

	// Load face contour from [0 - 26].
	auto faceBegin = points.begin();
	auto faceEnd = points.begin() + 27;
	faceContour.reserve(faceEnd - faceBegin);
	std::copy(faceBegin, faceEnd, std::back_inserter(faceContour));

	// Load left eye contour from [36 - 41].
	auto leftEyeBegin = points.begin() + 36;
	auto leftEyeEnd = points.begin() + 42;
	leftEyeOriginContour.reserve(leftEyeEnd - leftEyeBegin);
	std::copy(leftEyeBegin, leftEyeEnd, std::back_inserter(leftEyeOriginContour));

	// Load right eye contour from [42 - 48].
	auto rightEyeBegin = points.begin() + 42;
	auto rightEyeEnd = points.begin() + 48;
	rightEyeOriginContour.reserve(rightEyeEnd - rightEyeBegin);
	std::copy(rightEyeBegin, rightEyeEnd, std::back_inserter(rightEyeOriginContour));

	// Compute face centroid.
	faceCentroid = Utils::computeContourCentroid(faceContour);

	// Scale eye contours to 125%.
	Utils::scaleContour(leftEyeOriginContour, 1.25, leftEyeScaledContour);
	Utils::scaleContour(rightEyeOriginContour, 1.25, rightEyeScaledContour);

	// Rotate eye contours around face centroid on 15 degrees.
	Utils::rotateContour(leftEyeScaledContour, faceCentroid, 15, leftEyeRotatedContour);
	Utils::rotateContour(rightEyeScaledContour, faceCentroid, -15, rightEyeRotatedContour);

	// Colors.
	faceColor = QColor::fromRgba(qRgba(167, 127, 49, 255));
	centroidColor = QColor::fromRgba(qRgba(255, 255, 0, 255));
	originEyeColor = QColor::fromRgba(qRgba(255, 0, 0, 128));
	scaledEyeColor = QColor::fromRgba(qRgba(0, 255, 0, 128));
	rotatedEyeColor = QColor::fromRgba(qRgba(0, 0, 255, 128));
}

void TestGLWindow::drawPoint(const QPointF &point, const QColor &color) {
	glColor4f(color.redF(), color.greenF(), color.blueF(), color.alphaF());
	glBegin(GL_POINTS);
	glVertex2f(point.x(), point.y());
	glEnd();
}

void TestGLWindow::drawContour(const QVector<QPointF> &contour, const QColor &color) {
	glColor4f(color.redF(), color.greenF(), color.blueF(), color.alphaF());
	glBegin(GL_POLYGON);
	for (const QPointF &point : contour) {
		glVertex2f(point.x(), point.y());
	}
	glEnd();
}

void TestGLWindow::initializeGL() {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_PROGRAM_POINT_SIZE);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glPointSize(10.0f);
}

void TestGLWindow::resizeGL(int w, int h) {
	glViewport(0, 0, w, h);
}

void TestGLWindow::paintGL() {
	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();
	glTranslatef(0.5f, 0.5f, 0.0f);
	glRotatef(180, 0.0f, 1.0f, 0.0f);
	glRotatef(180, 1.0f, 0.0f, 0.0f);
	drawContour(faceContour, faceColor);

	glLoadIdentity();
	glTranslatef(-0.5f, 0.5f, 0.0f);
	glRotatef(180, 1.0f, 0.0f, 0.0f);
	drawContour(faceContour, faceColor);

	drawContour(leftEyeOriginContour, originEyeColor);
	drawContour(rightEyeOriginContour, originEyeColor);

	drawContour(leftEyeScaledContour, scaledEyeColor);
	drawContour(rightEyeScaledContour, scaledEyeColor);

	drawContour(leftEyeRotatedContour, rotatedEyeColor);
	drawContour(rightEyeRotatedContour, rotatedEyeColor);

	drawPoint(faceCentroid, centroidColor);

	glFlush();
}
