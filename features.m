clear;

load('features_annotations_EvaluationImages.txt');
load('features_annotations_GalleryImages.txt');
load('features_annotations_ProbeImages.txt');

load('labels_annotations_EvaluationImages.txt');
load('labels_annotations_GalleryImages.txt');
load('labels_annotations_ProbeImages.txt');

save('local_features_rank1-16-12', 'features_annotations_EvaluationImages',...
  'features_annotations_GalleryImages', 'features_annotations_ProbeImages',...
  'labels_annotations_EvaluationImages', 'labels_annotations_GalleryImages',...
  'labels_annotations_ProbeImages');

% figure;
% hold on
% grid on
% plot(features_annotations_GalleryImages(1,:), 'b');
% axis tight
% hold off
% pause;

figure;
hold on
for x = 1 : size(features_annotations_GalleryImages, 1)
    subplot(2,2,1);
    plot(features_annotations_GalleryImages(x,:), 'b');
    axis tight
    subplot(2,2,3);
    plot(features_annotations_ProbeImages(x,:), 'r');
    axis tight
    subplot(2,2,4);
    plot(features_annotations_EvaluationImages(x,:), 'g');
    axis tight
    pause;
end
hold off
close all;