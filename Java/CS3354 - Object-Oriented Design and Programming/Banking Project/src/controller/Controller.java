package controller;

import model.Model;
import view.View;

public interface Controller
{
	void setModel(Model model);
	Model getModel();
	View getView();
	void setView(View view);
}
