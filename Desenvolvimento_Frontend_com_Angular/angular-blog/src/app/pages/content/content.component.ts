import { Component, OnInit } from '@angular/core';
import { ActivatedRoute } from '@angular/router';
import { noticias } from 'src/app/data/data';

@Component({
  selector: 'app-content',
  templateUrl: './content.component.html',
  styleUrls: ['./content.component.css']
})
export class ContentComponent implements OnInit {

  photoCover:string = ""
  contentTitle:string = ""
  contentDescription:string = ""
  private id:number | null = 0

  constructor(private route:ActivatedRoute) { }

  ngOnInit(): void {
    this.route.paramMap.subscribe(value => {
      const idString = value.get('id'); // Obter o parâmetro 'id' como string
      this.id = idString ? +idString : null; // Converter para número ou manter como nulo se for nulo
      this.setValuesToComponent(this.id);
    });

  }

  setValuesToComponent(id:number | null){
    const result =noticias.filter(article => article.id == id)[0]

    this.contentTitle = result.title
    this.contentDescription = result.description
    this.photoCover = result.photoCover
  }

}
