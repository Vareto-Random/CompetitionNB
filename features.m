%load('features_annotations_EvaluationImages.txt');
load('features_annotations_GalleryImages15.txt');
%load('features_annotations_ProbeImages.txt');

%load('labels_annotations_EvaluationImages.txt');
%load('labels_annotations_GalleryImages15.txt');
%load('labels_annotations_ProbeImages.txt');

% save('local_features_rank1-08-07', 'features_annotations_EvaluationImages',...
%  'features_annotations_GalleryImages', 'features_annotations_ProbeImages',...
%  'labels_annotations_EvaluationImages', 'labels_annotations_GalleryImages',...
%  'labels_annotations_ProbeImages');

save('local_features_gallery', 'features_annotations_GalleryImages15');

%load('local_features.mat');
figure;
for x = 1 : size(features_annotations_GalleryImages15, 1)
    subplot(2,2,1);
    plot(features_annotations_GalleryImages15(x,:), 'b');
%     subplot(2,2,3);
%     plot(features_annotations_ProbeImages(x,:), 'r');
%     subplot(2,2,4);
%     plot(features_annotations_EvaluationImages(x,:), 'g');
    pause;
end
close all;